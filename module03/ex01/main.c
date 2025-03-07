/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:52 by tissad            #+#    #+#             */
/*   Updated: 2025/03/07 18:29:58 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define RED (1<<PORTD5) //0b100000
#define GREEN (1<<PORTD6) //0b1000000
#define BLUE (1<<PORTD3) //0b1000

#define YELLOW (RED | GREEN) //0b1100000
#define CYAN (GREEN | BLUE) //0b1001000
#define MAGENTA (RED | BLUE) //0b100100
#define WHITE (RED | GREEN | BLUE) //0b1101000

static uint8_t colors[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE};

// program control the LED RGB D5
int main(void)
{
     // output mode for D5, D3 and D6
    DDRD |= (1 << PD5) | (1 << PD3) | (1<<PD6); //0b1101000
    PORTD = 0b0; // set all pins to low

    while (1)
    {
        for (uint8_t i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
        {
            PORTD |= colors[i];
            _delay_ms(1000);
            PORTD &= ~colors[i];
        }
    }
    return 0;
}