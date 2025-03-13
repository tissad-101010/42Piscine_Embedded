/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 19:28:38 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>
#include <adc.h>

char BUF[17];
int main(void)
{

	uart_init(UBRR);
	while (1)
	{
        uint16_t pot = ADC_read(0);  // Potentiomètre RV1 (ADC0)
        uint16_t ldr = ADC_read(1);  // LDR R14 (ADC1)
        uint16_t ntc = ADC_read(2);  // NTC R20 (ADC2)

        itoa_base(pot, BUF, DECIMAL);
		uart_puts(BUF);
		uart_puts(", ");
		itoa_base(ldr, BUF, DECIMAL);
		uart_puts(BUF);
		uart_puts(", ");
		itoa_base(ntc, BUF, DECIMAL);
		uart_puts(BUF);
		uart_puts("\n\r");

        _delay_ms(200); //use 20 ms
	}
		
	return (0);
}

ISR(ADC_vect)
{
	

}