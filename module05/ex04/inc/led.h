/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   led.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:25:42 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 15:48:48 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LED_H

# define LED_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void ddr_init();
void rgb_init();
void set_led(uint8_t pos);

#endif