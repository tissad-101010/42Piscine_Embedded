/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:05:08 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 20:03:48 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <i2c.h>
#include <timer.h>
#include <uart.h>


int main(void)
{
    timer_init();
    i2c_init();
    uart_init(UBRR);
    while (1)
    {

    }
    
    return 0;
}

ISR(TIMER1_OVF_vect)
{
    // code to be executed every 20ms
   
    uint8_t status = i2c_start();
    i2c_stop();
    uart_putnbr(status, HEXA);
    uart_puts("\n\r"); 
}