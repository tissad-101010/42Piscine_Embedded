/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/06 15:50:05 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#define NF 500


int main(void) {
	// set PB1 as output
	DDRB |= (1 << DDB1); // 0b10

	// COM1A1 bit that enables the toggle mode
	// set the timer TCCR1 to fast PWM mode
	// FAST PWM mode: the counter counts from 0 to ICR1 then resets 
	// WGM13:0 = 14 (WGM13=1, WGM12=1, WGM11=1, WGM10=0)
	// CS12 and CS10 bit that sets the prescaler to 256 on TCCR1B
	// TCCR1A |COM1A1|COM1A0|COM1B1|COM1B0|-|-|WGM11|WGM10|
	TCCR1A = (1 << COM1A1) | (1 << WGM11);//0b10000010
	// TCCR1B |ICNC1|ICES1|-|WGM13|WGM12|CS12|CS11|CS10|
	TCCR1B = (1 << WGM12 ) | (1 << WGM13) | (1 << CS12); // 0b00011100
	// Prescaler = 256, F_CPU = 16MHz donc 16MHz / 256 = 62500Hz < 65535Hz (2^16)
	// ICR1 used to set the top value of the counter 
	ICR1 = (uint16_t) (F_CPU / 256); // 62500
	// for 1 hz we need 10% of the top value 6250
	// OCR1A used to set the compare value of the counter
	OCR1A = (uint16_t) (ICR1 * 0.1); // 6250
	// the difference between the top value and the compare value is the duty cycle 
	while (1) {

	}
	
	return 0;
}
