/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:08:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/06 17:08:15 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

static inline void  delay_loop(uint32_t count) {
    while (count--) {
    	__asm__("nop"); // No Operation ~
    }
}

int main(void) {
	DDRB |= 0b10;// PB1 as output
	while (1)
	{
		
		delay_loop((uint32_t)(F_CPU * 0.05)); // ~ 0.5 s when F_CPU = 16 MHz
		PORTB ^= (1 << PB1); // Toggle the LED
	}
	return 0;
}