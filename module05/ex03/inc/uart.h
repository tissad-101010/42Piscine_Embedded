/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:26:16 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 12:33:06 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UART_H
# define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define HEXA "0123456789ABCDEF"
#define BINARY "01"
#define OCTAL "01234567"
#define DECIMAL "0123456789"


#define BAUD 115200
#define UBRR F_CPU/8/BAUD-1

void uart_init(uint16_t ubrr);
void uart_tx(char data);
char uart_rx(void);
void uart_puts(const char *str);
void uart_putnbr(int32_t value, char *base);
void itoa_base(int32_t value, char *buffer, char *base);


#endif