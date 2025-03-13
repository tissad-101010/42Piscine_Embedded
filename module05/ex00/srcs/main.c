/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 15:40:26 by tissad           ###   ########.fr       */
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
	uint8_t adc_value = ADC_read();
	char buffer[5];
	itoa_base(adc_value, buffer, HEXA);
	uart_puts(buffer);
	uart_puts("\n\r");
	_delay_ms(20);
}