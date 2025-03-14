/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:32:55 by tissad            #+#    #+#             */
/*   Updated: 2025/03/14 18:21:22 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uart.h>
#include <adc.h>

// #define TS_GAIN 1.22   // Valeur approximative
// #define TS_OFFSET 352  // Décalage approximatif


#define TS_GAIN_ADDRESS  0x0003
#define TS_OFFSET_ADDRESS 0x0002

// Fonction pour lire un octet depuis la "signature row"
int read_signature_byte(uint16_t address) {
    while (SPMCSR & (1 << SPMEN));  // Attendre que SPMEN soit libre

    SPMCSR = (1 << SIGRD) | (1 << SPMEN);  // Activer la lecture de la signature row

    int result;
    __asm__ __volatile__(
        "lpm %0, Z\n"   // Charger la valeur depuis l'adresse Z dans result
        : "=r" (result) // Stocker la valeur dans result
        : "z" (address) // Utiliser address comme registre Z
    );

    return result;
}

int16_t ConvertToCelsius(uint16_t adc_value, int TS_GAIN, int TS_OFFSET)
{
/** https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#G1202807
 * Formula from datasheet: 25°C / 352mV -> 0.071022727 mV/°C
 *  */
	float temperature = (((adc_value - 273 + 100 - TS_OFFSET) * 128) / TS_GAIN) + 25;
	return (int16_t)(temperature);
}

int main(void)
{
	uart_init(UBRR);
	ADC_init();
	while (1);
	return (0);
}

ISR(ADC_vect)
{
	int ts_gain = read_signature_byte(TS_GAIN_ADDRESS);
    int ts_offset = read_signature_byte(TS_OFFSET_ADDRESS);
	uint16_t adc_value = ADC_read();
	int32_t temperature = ConvertToCelsius(adc_value,ts_gain,ts_offset);
	uart_putnbr(temperature, DECIMAL);
	uart_puts("\n\r");
	_delay_ms(20);
}