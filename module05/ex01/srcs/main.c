/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 18:03:46 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>
#include <adc.h>

char BUF[5];
int main(void)
{

	
	uart_init(UBRR);
	ADC_init();
	while (1)
	{
		itoa_base(ADC_get_pot(), BUF, HEXA);
		uart_puts(BUF);
		uart_puts(", ");
		itoa_base(ADC_get_ldr(), BUF, HEXA);
		uart_puts(BUF);
		uart_puts(", ");
		itoa_base(ADC_get_ntc(), BUF, HEXA);
		uart_puts(BUF);
		uart_puts("\n\r");
		_delay_ms(20);
	}
		
	return (0);
}

ISR(ADC_vect)
{
	

}