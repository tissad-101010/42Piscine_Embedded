/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:08:54 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 20:21:36 by tissad           ###   ########.fr       */
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

void i2c_write(uint8_t data) {
	
    // TWDR is the I2C Data Register
	TWDR = data;
	// TWCR is the I2C Control Register
	// TWEN: TWI Enable Bit
	// TWINT: TWI Interrupt Flag
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); 
}

uint8_t i2c_read_ack(void) {
	
	// TWCR is the I2C Control Register
	// TWEA: TWI Enable Acknowledge Bit
	// TWEN: TWI Enable Bit
	// TWINT: TWI Interrupt Flag
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	
	// Wait for TWINT Flag set. This indicates that the data has been received
	while (!(TWCR & (1 << TWINT)));
	
	// Return received data
	return (TWDR);
}