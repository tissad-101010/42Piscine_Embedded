/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:09:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 16:33:06 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <adc.h>


void ADC_init()
{
    // Set the reference voltage to AVCC with a left adjust result
    // REFS0 = 1, REFS1 = 0 to select AVCC as reference voltage 5V
    // ADLAR = 1 to left adjust the result

    ADMUX |= (1 << REFS0);
    // select the RV1 as input
    // MUX3:0 = 0000 to select the ADC0 pin;   
    // Enable the ADC and start the conversion
    // ADEN = 1 to enable the ADC
    // ADSC = 1 to start the conversion
    // ADPS0 = 1 and ADPS1 = 1 to set the prescaler to 8
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS1) | (1 << ADPS0);
    // // enable adc interrupt
    ADCSRA |= (1 << ADIE);
    // // enable global interrupt
    sei();
}

uint16_t ADC_read()
{
    _delay_ms(1);
    ADCSRA |= (1 << ADSC);
    // Wait until the conversion is complete
    // ADSC = 1 while the conversion is in progress
    while (ADCSRA & (1 << ADSC));
    // Return the ADC value
    return (ADC);
}

uint16_t ADC_get_pot()
{
    // select the RV1 as input
    // MUX3:0 = 0000 to select the ADC0 pin;
    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);

    return (ADC_read());
}

uint16_t ADC_get_ldr()
{

    // MUX3:0 = 0001 to select the ADC1 pin;   
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);
    ADMUX |= (1 << MUX0);
    return (ADC_read());
}

uint16_t ADC_get_ntc()
{

    // MUX3:0 = 0010 to select the ADC2 pin;   
    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);
    ADMUX |= (1 << MUX1);
    return (ADC_read());
}