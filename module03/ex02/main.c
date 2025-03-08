/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/08 11:50:48 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_rgb();
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
void wheel(uint8_t pos);

uint8_t  pos = 0;

int main(void) {
    init_rgb();
    sei();
    while (1) {
    }

    return 0;
}

void init_rgb() {
    // PD6 (OC0A), PD5 (OC0B) et PD3 (OC2B) as output
    DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3);

    // Fast PWM mode for Timer0 and Timer2
    // WGM00 WGM01 to set Fast PWM mode on Timer0
    TCCR0A |= (1 << WGM00) | (1 << WGM01); //0b11
    // COM0A1 COM0B1 to set non-inverting mode
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1); //0b110000
    // CS01 to set prescaler 8
    TCCR0B |= (1 << CS01); //0b010

    // WGM20 WGM21 to set Fast PWM mode on Timer2
    TCCR2A |= (1 << WGM20) | (1 << WGM21); 
    // COM2B1 to set non-inverting mode
    TCCR2A |= (1 << COM2B1); 
    // CS21 to set prescaler 8
    TCCR2B |= (1 << CS21);

    // Timer1   
    // Mode CTC, OCR1A as top
    TCCR1B |= (1 << WGM12);
    // Prescaler 64 (16MHz / 64 = 250 kHz, donc 1 tick = 4µs)
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // (250 kHz * 100 ms = 25000 ticks) interrupt every 100 ms
    OCR1A = 25000;
    TIMSK1 |= (1 << OCIE1A); // Enable interrupt on compare match
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    // set the duty cycle
    // OCR0A for red (PD5)
    OCR0A = r; 
    // OCR0B for green (PD6)
    OCR0B = g;
    // OCR2B for blue (PD3)
    OCR2B = b;
}

void wheel(uint8_t pos) {
    pos = 255 - pos;
    if (pos < 85) {
        set_rgb(255 - pos * 3, 0, pos * 3);
    } else if (pos < 170) {
        pos -= 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    } else {
        pos -= 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

ISR(TIMER1_COMPA_vect) {
    pos++;
    if (pos > 255) pos = 0; 
    wheel(pos);
}