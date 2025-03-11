/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:16:15 by tissad            #+#    #+#             */
/*   Updated: 2025/03/11 18:19:12 by tissad           ###   ########.fr       */
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
    DDRB |= (1 << PB1); 

    timer0_init(); 
    timer1_init();  
    
    sei();
    
    while (1);
}


void timer0_init(void)
{
    // Mode CTC 
    TCCR0A = (1 << WGM01); 
    // Prescaler 1024
    TCCR0B = (1 << CS02) | (1 << CS00); 
    // OCR0A =  10 ms
    OCR0A = (F_CPU / 1024 * 0.01);
    // Enable interrupt on compare match
    TIMSK0 = (1 << OCIE0A); 
}


void timer1_init(void)
{
    // Mode PWM 8 bits
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    // prescaler 1
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);  
    // ICR1 max value
    ICR1 = 0xFF;
    // Duty cycle 
    OCR1A = 0; 
}


ISR(TIMER0_COMPA_vect)
{
    OCR1A = duty_cycle;  
    
    duty_cycle += step; 
    
    if (duty_cycle == ICR1 || duty_cycle == 0)
        step = -step; 
}
