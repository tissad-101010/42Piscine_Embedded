/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 12:17:29 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>
#include <adc.h>

int main(void)
{

	
	uart_init(UBRR);
	ADC_init();
	while (1)
	{

	}
		
	return (0);
}

ISR(ADC_vect)
{
	uart_putnbr(ADC_get_pot(), DECIMAL);
	uart_puts(", ");
	uart_putnbr(ADC_get_ldr(), DECIMAL);
	uart_puts(", ");
	uart_putnbr(ADC_get_ntc(), DECIMAL);
	uart_puts("\n\r");
	_delay_ms(20);
}