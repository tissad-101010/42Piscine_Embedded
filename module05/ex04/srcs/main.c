/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 15:52:03 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>
#include <adc.h>
#include <led.h>
#include <timer.h>

int main(void)
{
	uart_init(UBRR);
	adc_init();
	ddr_init();
	rgb_init();
	timer_init();
	while (1);
	return (0);
}


ISR(TIMER1_OVF_vect)
{
	uint8_t result = adc_read();
	set_led(result);
	
	uart_putnbr(result, DECIMAL);
	uart_puts("\n\r");
}