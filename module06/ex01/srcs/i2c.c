/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:08:54 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 19:58:22 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <i2c.h>

void i2c_init(void) {

	TWSR = 0x00; 
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2; 
}

uint8_t  i2c_start(void) {

	// TWCR is the I2C Control Register
	// TWSTA: TWI Start Condition Bit
	// TWEN: TWI Enable Bit
	// TWINT: TWI Interrupt Flag
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	// Wait for TWINT Flag set. This indicates that the START condition has been transmitted
	while (!(TWCR & (1 << TWINT)));
	
	// Return TWI Status Register, mask the prescaler bits (TWPS1, TWPS0)
	uint8_t status = TWSR;
	
	return (status);
}

void i2c_stop(void) {

	// TWCR is the I2C Control Register	
	// TWSTO: TWI Stop Condition Bit
	// TWINT: TWI Interrupt Flag
	// TWEN: TWI Enable Bit

	TWCR = (1 << TWSTO);
	
	// Wait for a STOP condition to be  
	// transmitted on the bus
	
	//while (TWCR & (1 << TWSTO));
	// TWINT is set by hardware to indicate that the STOP condition has been transmitted
}