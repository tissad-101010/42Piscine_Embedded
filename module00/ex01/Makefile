# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tissad <tissad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 11:23:37 by tissad            #+#    #+#              #
#    Updated: 2025/03/04 12:19:43 by tissad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# atmega328p is the microcontroller used in the board
MCU=atmega328p
# 16MHz is the default clock speed of the board
F_CPU=16000000
# avr-gcc is the compiler for AVR microcontrollers
CC=avr-gcc
# avr-objcopy is a utility to copy and translate object files
OBJCOPY=avr-objcopy
# avrdude is a utility to download/upload/manipulate the ROM and EEPROM contents\
 of AVR microcontrollers using the in-system programming technique (ISP)\
 through the USB port 
AVRDUDE=avrdude

# arduio is the programmer used to flash the board
ISP_PROG=arduino
# /dev/ttyUSB0 is the port where the board is connected
ISP_PORT=/dev/ttyUSB0
# 115200 bits/s is the baudrate used to communicate with the board
ISP_BAUDRATE=115200

TARGET=main
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)


all: hex flash

hex:
	$(CC) $(CFLAGS) -o $(TARGET).bin $(TARGET).c
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).bin $(TARGET).hex

flash:
	$(AVRDUDE) -c $(ISP_PROG) -p $(MCU) -P $(ISP_PORT) -b $(ISP_BAUDRATE) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).bin $(TARGET).hex

.PHONY: all hex flash clean
# **************************************************************************** #