/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   led.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:25:07 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 15:48:25 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <led.h>

void ddr_init() 
{
	// PD6 (OC0A), PD5 (OC0B) et PD3 (OC2B) as output
	DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6);
	DDRB |= (1 << DDB0)|(1 << DDB1)|(1 << DDB2) | (1 << DDB4);
}

void rgb_init() 
{
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
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	// set the duty cycle
	// OCR0A for red (PD5)
	OCR0B = r; 
	// OCR0B for green (PD6)
	OCR0A = g;
	// OCR2B for blue (PD3)
	OCR2B = b;
}

void wheel(uint8_t pos)
{
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

void set_led(uint8_t pos)
{
	wheel(pos);
	if (pos >= UINT8_MAX/4)
		PORTB |= (1 << PORTB0);
	else
		PORTB &= ~(1 << PORTB0);
	if (pos >= UINT8_MAX/2)
		PORTB |= (1 << PORTB1);
	else
		PORTB &= ~(1 << PORTB1);
	if (pos >= UINT8_MAX/4 * 3)
		PORTB |= (1 << PORTB2);
	else
		PORTB &= ~(1 << PORTB2);
	if (pos == UINT8_MAX)
		PORTB |= (1 << PORTB4);
	else
		PORTB &= ~(1 << PORTB4);
}