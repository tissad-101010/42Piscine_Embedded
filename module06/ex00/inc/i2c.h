/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:09:43 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 19:23:56 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I2C_H
# define I2C_H

# include <avr/io.h>
#include <util/twi.h>
# include <avr/interrupt.h>
# include <util/delay.h>

#define SCL_CLOCK 100000L // Fréquence I2C de 100 kHz

void i2c_init(void);
uint8_t i2c_start(void);
void i2c_stop(void);

#endif