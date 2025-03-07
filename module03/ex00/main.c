/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/07 18:01:54 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// program control the LED RGB D5
int main(void)
{
    DDRD |= (1 << PD5) | (1 << PD3) | (1<<PD6);  // output mode for D5, D3 and D6
    PORTD = 0b0; // set all pins to low

    while (1)
    {
        PORTD |= (1<<PORTD5); // turn on the LED D5 (red) 
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD5); // turn off the LED D5 (red)
        PORTD |= (1<<PORTD6); // turn on the LED D3 (green)
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD6); // turn off the LED D3 (green)
        PORTD |= (1<<PORTD3); // turn on the LED D6 (blue)  
        _delay_ms(1000);
        PORTD &= ~(1<<PORTD3); // turn off the LED D6 (blue)
    }
    return 0;
}