/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:16:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/07 16:16:52 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200 
#define MYUBRR F_CPU/8/UART_BAUDRATE-1 


static inline void uart_init(uint16_t ubrr);
static inline void timer_init(void);
static inline void uart_tx(uint8_t c);
static inline void uart_printstr(char *str);

int main(void) {
    uart_init(MYUBRR); 
    timer_init();       
    sei();
    while (1);
    return 0;
}

// UART initialization
static inline void uart_init(uint16_t ubrr) {
	// UCSR0A is the USART Control and Status Register A
	// U2X0: Double the USART Transmission Speed
    UCSR0A |= (1 << U2X0);
    UBRR0H = (uint8_t)(ubrr >> 8); // Set baud rate
    UBRR0L = (uint8_t)ubrr; // Set baud rate
	// UCSR0B is the USART Control and Status Register B
	// RXEN0: Receiver Enable
    UCSR0B = (1 << TXEN0); // Transmitter Enable
	// UCSR0C is the USART Control and Status Register C	
	// UCSZ01 = 1 and UCSZ00 = 1 sets the data size to 8-bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set frame format: 8data, 1stop bit 8N1
}


static inline void timer_init(void) {
	// TCCR1B is the Timer/Counter1 Control Register B
	// WGM12: Waveform Generation Mode
    TCCR1B |= (1 << WGM12); 
	// CS12, CS11, CS10: Clock Select, Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10); 
	// OCR1A is the Output Compare Register 1 A
	// Set the value that Timer1 will compare with
    OCR1A = (F_CPU / 1024 * 2) - 1;
	// TIMSK1 is the Timer/Counter1 Interrupt Mask Register	
	// OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);
}


static inline void uart_tx(uint8_t c) {
	// UCSR0A is the USART Control and Status Register A	
	// UDRE0: USART Data Register Empty
    while (!(UCSR0A & (1 << UDRE0)));
	// UDR0 is the USART I/O Data Register
    UDR0 = c;
}


static inline void uart_printstr(char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}

ISR(TIMER1_COMPA_vect) {
    uart_printstr("Hello World!\n\r");
}
