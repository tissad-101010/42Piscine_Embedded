/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:16:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/08 12:33:42 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200 // UART_BAUDRATE rate
#define UBRR (uint16_t)(F_CPU/8/UART_BAUDRATE-1) 
// USART Universal Synchronous and Asynchronous serial Receiver and Transmitter
// USART is a way to communicate between devices. It is a serial communication protocol.

static inline void uart_init(uint16_t ubrr);
static inline void uart_tx(uint8_t data);
static inline void timer_init(void);

int main(void)
{
	uart_init(UBRR);
	timer_init();
	sei();
	while (1)
	{

	}
	
	return 0;
}

static inline void uart_init(uint16_t ubrr)
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
	// TXEN0: Transmitter Enable
	UCSR0B = (1<<TXEN0);
	//UCSR0C: |UMSEL01|UMSEL00|UPM01|UPM00|USBS0|UCSZ01|UCSZ00|UCPOL0
	// UCSZ01 = 1 and UCSZ00 = 1 sets the data size to 8-bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 0b110
}

static inline void timer_init(void) {
	// TCCR1B is the Timer/Counter1 Control Register B
	// WGM12: Waveform Generation Mode
    TCCR1B |= (1 << WGM12); 
	// CS12, CS11, CS10: Clock Select, Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); 
	// OCR1A is the Output Compare Register 1 A
	// Set the value that Timer1 will compare with
    OCR1A = (F_CPU / 1024 * 2); // =  15625 < 65536 1hz
	// TIMSK1 is the Timer/Counter1 Interrupt Mask Register	
	// OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);
}

static inline void uart_tx(uint8_t data) {
	
    while (!(UCSR0A & (1 << UDRE0)))// Wait until data register is empty
        ;
	// UCSR0A is the USART Control and Status Register A
	// UDRE0: USART Data Register Empty
	// UDR0 is the USART buffer
	// if UDRE0 is set, the buffer is empty and can be written to
    UDR0 = data;
}

// ISR is a macro that tells the compiler that the function is an interrupt service routine
ISR(TIMER1_COMPA_vect) {
	uart_tx('Z');
}