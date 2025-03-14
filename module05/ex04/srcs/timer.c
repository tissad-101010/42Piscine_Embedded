/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:43:30 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 15:45:05 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <timer.h>

void timer_init()
{
	// set timer1 fast pwm mode
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	
	// set prescaler to 64
	//TCCR1B |= (1 << CS11) | (1 << CS10);
	// set the prescaler to 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set the compare match register to 25000
	ICR1 = F_CPU / 1024 * 0.02;
	// enable overflow interrupt
	TIMSK1 |= (1 << TOIE1);
	// enable global interrupt
	sei();
}