/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:25:05 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 15:58:28 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>



void uart_init(uint16_t ubrr)
{

	// UCSR0A is the USART Control and Status Register A
	// U2X0: Double the USART Transmission Speed
	UCSR0A |= (1 << U2X0);
	/*Set baud rate */
	// UBBR0 is the USART Baud Rate Register
	// Baud rate is calculated as follows:
	// Baud rate is used to set the speed of communication between the devices.
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr; 

	// UCSRB is the USART Control and Status Register B
	// RXEN0: Receiver Enable
	// TXEN0: Transmitter and Receiver Enable 
	// RXCIE0: RX Complete Interrupt Enable
	// UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0B = (1 << TXEN0);
	// UCSR0C: |UMSEL01|UMSEL00|UPM01|UPM00|USBS0|UCSZ01|UCSZ00|UCPOL0
	// UCSZ01 = 1 and UCSZ00 = 1 sets the data size to 8-bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 0b110

}

// Function to send data (character)
void uart_tx(char data) 
{
	
	while (!(UCSR0A & (1 << UDRE0)))// Wait until data register is empty
		;
	// UCSR0A is the USART Control and Status Register A
	// UDRE0: USART Data Register Empty
	// UDR0 is the USART buffer
	// if UDRE0 is set, the buffer is empty and can be written to
	UDR0 = data;
}

// Function to receive data (character)
char uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0)))// Wait until data is received
		;
	char data = UDR0;
	return (data);
}


// Function to send string
void uart_puts(const char *str)
{
	while (*str)
	{
		uart_tx(*str);
		str++;
	}
}

void uart_putnbr(int32_t n, char *base)
{
	char BUFFER[16];
	itoa_base(n, BUFFER, base);
	uart_puts(BUFFER);
}
