/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:08:25 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 19:28:29 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADC_H
# define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_POT 0b0
#define ADC_LDR 0b1
#define ADC_NTC 0b10

uint16_t ADC_read(uint8_t channel);


#endif