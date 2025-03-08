/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/04 14:00:19 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

// Static variable to store the value of the LED
static int8_t v = 0;

// Function to setup the microcontroller
void setup() {
	// LED set up
	// LED D1
	DDRB |= 0b10111;    // set PB0, PB1, PB2, PB4 as output (LED) => 1
	PORTB = 0b0;   // set all the LEDs to 0
	// Button SW set up
	// set PORTD as input SW1 (PD2) and SW2 (PD4)
	DDRD = 0b0;
}

// Fuction that increment the value of v when the button SW1 is pressed
void routine1() {
	if (!(PIND & (1 << PD2))) // check if the button is pressed (PD2 = 0)
	{ 
		v++;
		if (v == 0b1000) 		// v == 8
			v =  0b10000;		// v = 16 LED D4 is on
		if (v > 0b10111)		// if v > 23
			v =  0b0;			// v = 0 all the LEDs are off
		PORTB = v;	
		while (!(PIND & (1 << PD2))); // wait for the button to be released (debounce )
	}
}

// Fuction that decrement the value of v when the button SW2 is pressed
void routine2() {
	if (!(PIND & (1 << PD4))) // check if the button is pressed (PD4 = 0)
	{ 
			// if v > 0
		v--;					// decrement v
		if (v < 0b0) 			// if v < 0
			v = 0b10111;		// LED D1, D2, D3, D4 are on
		if (v == 0b01111)		// if v = 15
			v =  0b111;			// LED D1 D2 D3 are on
		PORTB = v;			
		while (!(PIND & (1 << PD4))); // wait for the button to be released (debounce )
	}
}

// Function to handle the routine
void routine() {
	routine1();
	routine2();
	_delay_ms(20);
}

int main(void) {
	setup();
	while (1)
		routine();
	return 0;
}