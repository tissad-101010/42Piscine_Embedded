/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 16:31:28 by tissad           ###   ########.fr       */
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
	uart_putnbr(ADC_get_pot(), HEXA);
	uart_puts(", ");
	uart_putnbr(ADC_get_ldr(), HEXA);
	uart_puts(", ");
	uart_putnbr(ADC_get_ntc(), HEXA);
	uart_puts("\n\r");
	_delay_ms(20);
}