/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/04 12:23:14 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

// Function to setup the microcontroller
void setup() {
	DDRB = 0b1;		// set PB0 as output (LED) 1
	PORTB = 0b0;	// set the LED to 0
	DDRD = 0b0;		// set PD2 as input (Button) 0
}

// Function to handle the routine
void routine() {

	if (!(PIND & (1 << PD2))) // check if the button is pressed (PD2 = 0)
	{ 
		PORTB ^= (1 << PB0);  // toggle the LED state (XOR)
		while (!(PIND & (1 << PD2))); // wait for the button to be released (debounce )
	}
	_delay_ms(20); // delay for 20ms
}

int main(void) {
	setup();
	while (1)
		routine();
	return 0;
}