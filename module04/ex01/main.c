/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:16:15 by tissad            #+#    #+#             */
/*   Updated: 2025/03/11 18:09:04 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t duty_cycle = 0;
volatile int8_t step = 1;  // Incrément ou décrément

void timer0_init(void);
void timer1_init(void);

int main(void)
{
    DDRB |= (1 << PB1);  // PB1 en sortie (OC1A)

    timer0_init();  // Timer0 pour l'interruption toutes les 10ms
    timer1_init();  // Timer1 pour le PWM
    
    sei();  // Activation des interruptions globales
    
    while (1);
}

// -------------------- Configuration de Timer0 --------------------
void timer0_init(void)
{
    TCCR0A = (1 << WGM01);  // Mode CTC
    // frequence 1hz with prescaler 1024
    TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler 1024
    OCR0A = (F_CPU / 1024 * 0.01);  // 10ms
    TIMSK0 = (1 << OCIE0A);  // Activation de l'interruption compare match A
}

// -------------------- Configuration de Timer1 (PWM) --------------------
void timer1_init(void)
{
    TCCR1A = (1 << COM1A1) | (1 << WGM11);  // Mode PWM rapide, sortie non inversée
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);  // Pas de prescaler (16MHz)
    ICR1 = 255;  // Période du PWM (8-bit : 255 → fréquence élevée)
    OCR1A = 0;  // Initialisation du rapport cyclique à 0%
}

// -------------------- Gestion de l'Interruption Timer0 --------------------
ISR(TIMER0_COMPA_vect)
{
    OCR1A = duty_cycle;  // Appliquer le rapport cyclique au Timer1
    
    duty_cycle += step;  // Incrémenter ou décrémenter
    
    if (duty_cycle == 255 || duty_cycle == 0)
        step = -step;  // Inverser la direction (0→255 ou 255→0)
}
