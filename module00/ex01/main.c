/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/03 15:04:44 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// programe that actives the LED D1 (PB0) on the atmega328p microcontroller
// use avr/io.h to access the registers of the microcontroller 
#include <avr/io.h>

// use only the AVR registers (DDRX, PORTX, PINX) to manipulate the microcontroller

int main(void)
{
	// set the data direction register B to 0b00000001
	// this will set the PB0 pin as an output
	DDRB = 0b0000001;

	// set the port B register to 0b00000001
	// this will set the PB0 pin to high
	PORTB = 0b00000001;

	
	return (0);
}