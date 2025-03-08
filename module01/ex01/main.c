/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/06 15:51:26 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#define NF 500


int main(void) {
	// set PB1 as output
    DDRB |= (1 << DDB1); // 0b10
	
	// COM1A0 bit that enables the toggle mode
	TCCR1A = (1 << COM1A0); // 0b00000010
	
	// WGM12 bit that enables the CTC mode
	// CS12 and CS10 bit that sets the prescaler to 1024
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // 0b00001101
	// Prescaler = 1024
	// F_CPU = 16MHz
	// 16MHz / 1024 = 15625Hz
	// OCR1A used to set the compare value of the counter
	// for 1 hz we need 15625 / 2 = 7812.5
	// so we set OCR1A to 7812
	// LED D2 is connected to PB1 which is the OC1A pin
    OCR1A = (uint16_t) ((F_CPU / 1024) * 0.5);

    while (1) {

    }
    
    return 0;
}
