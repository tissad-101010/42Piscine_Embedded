/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/04 11:59:09 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// programe that actives the LED D1 (PB0) on the board atmega328p microcontroller
// use avr/io.h to access the registers of the microcontroller 
#include <avr/io.h>
#include <util/delay.h>

// use only the AVR registers (DDRX, PORTX, PINX) to manipulate the microcontroller

int main(void)
{
	// set the data direction register B to 0b00000001
	// this will set the PB0 pin as an output
	DDRB = 0b00000001;
	PORTB = 0b00000000; // set the port B register to low


	// Configure PD2 as input
	DDRD = 0b00000000;
	
	while (1) {
        // check if the button is pressed
        if (!(PIND & 0b00000100)) {
			// set the port B register to 0b00000001
			// this will set the PB0 pin to high
            PORTB = 0b00000001;
        } else {
			// this will set the PB0 pin to low
            PORTB = 0b00000000;
        }
		// delay for 20ms to avoid debouncing
		_delay_ms(20);
    }
	return (0);
}