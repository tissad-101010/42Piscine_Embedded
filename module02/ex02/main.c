/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:16:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/07 15:17:26 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200 // UART_BAUDRATE rate
#define MYUBRR (uint16_t)(F_CPU/8/UART_BAUDRATE-1) 
// USART Universal Synchronous and Asynchronous serial Receiver and Transmitter
// USART is a way to communicate between devices. It is a serial communication protocol.

void uart_init(uint16_t ubrr);
void uart_tx(uint8_t data);
uint8_t uart_rx(void);

int main(void)
{
	uart_init(MYUBRR);
	while (1)
	{
		uint8_t data = uart_rx();
        //uart_tx('\n');
        //uart_tx('\r');
        uart_tx(data);
	}
	
	return 0;
}

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
	UCSR0B = (1<<TXEN0 | 1<<RXEN0);
	//UCSR0C: |UMSEL01|UMSEL00|UPM01|UPM00|USBS0|UCSZ01|UCSZ00|UCPOL0
	// UCSZ01 = 1 and UCSZ00 = 1 sets the data size to 8-bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 0b110
}

// function to send data
void uart_tx(uint8_t data) {
	
    while (!(UCSR0A & (1 << UDRE0)))// Wait until data register is empty
        ;
	// UCSR0A is the USART Control and Status Register A
	// UDRE0: USART Data Register Empty
	// UDR0 is the USART buffer
	// if UDRE0 is set, the buffer is empty and can be written to
    UDR0 = data;
}

// function to receive data
uint8_t uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)))// Wait until data is received
        ;
    uint8_t data = UDR0;
   (void)UDR0;
    return (data);
}