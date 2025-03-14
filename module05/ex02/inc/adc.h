/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:08:25 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 16:33:57 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADC_H
# define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ADC_POT 0b0
#define ADC_LDR 0b1
#define ADC_NTC 0b10

void ADC_init();
uint16_t ADC_read();
uint16_t ADC_get_pot();
uint16_t ADC_get_ldr();
uint16_t ADC_get_ntc();
#endif