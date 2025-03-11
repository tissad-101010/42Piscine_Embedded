/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:11:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/11 17:14:20 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

static inline void interrupt_init();
static inline void set_DDR(void);

int main()
{
	set_DDR();
	interrupt_init();
	
	while (1);
	return (0);
}	

static inline void interrupt_init() {
	
	// EICRA is the External Interrupt Control Register A
	// ISC01, ISC00: Interrupt Sense Control
	EICRA |= (1 << ISC01); // 0b10
    EICRA &= ~(1 << ISC00); // 0b0

	// EIMSK is the External Interrupt Mask Register
	// INT0: External Interrupt Request 0 Enable SW1 (PD2)
    EIMSK |= (1 << INT0);
	
	sei(); // Enable global interrupts
}

static inline void set_DDR(void)
{
	// set DDRB to output (LED D1)
	DDRB |= (1 << PB0); // 0b00000001
	// set DDRD to input (button SW1)
	DDRD &= ~(1 << PD2); // 0b11111011
}


ISR(INT0_vect)
{
	
	// disable global interrupts
	cli();
	EIMSK &= ~(1 << INT0);
	_delay_ms(300);
	PORTB ^= (1 << PB0);
	// clear interrupt flag
	EIFR |= (1 << INTF0);
	// enable interrupt
	sei();
	EIMSK |= (1 << INT0);
}
