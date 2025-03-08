/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/06 16:16:54 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
// F_CPU / 256 = 62500

void setupDDR() {
	// LED set up
	// LED D2
	DDRB |= 0b10;    // set PB1 as output
	// Button SW set up
	// set PORTD as input SW1 (PD2) and SW2 (PD4)
	DDRD = 0b0;
}

void setupTimer()
{
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
}

void routinePD2() {
	if (!(PIND & (1 << PD2))) // check if the button is pressed (PD2 = 0)
	{ 
		
		if (OCR1A >= ICR1) // check if the value of OCR1A is greater than ICR1
			OCR1A = ICR1; // set the value of OCR1A to ICR1
		else
			OCR1A += (uint16_t)(ICR1 * 0.1); // increment the value of OCR1A by 10% of ICR1(Top value)
		while (!(PIND & (1 << PD2))); // wait for the button to be released (debounce )
	}
}

// Fuction that decrement the value of v when the button SW2 is pressed
void routinePD4() {
	if (!(PIND & (1 << PD4))) // check if the button is pressed (PD4 = 0)
	{ 
		if (OCR1A <= (uint16_t)(ICR1 * 0.1)) // check if the value of OCR1A is less than 10% of ICR1
			OCR1A = (uint16_t)(ICR1 * 0.1); // set the value of OCR1A to 10% of ICR1
		else
			OCR1A -= (uint16_t)(ICR1 * 0.1); // decrement the value of OCR1A by 10% of ICR1(Top value)
		while (!(PIND & (1 << PD4))); // wait for the button to be released (debounce )
	}
}

int main(void) {

	setupDDR();
	setupTimer();

	while (1) {
		routinePD2();
		routinePD4();
		_delay_ms(20);
	}
	
	return 0;
}
