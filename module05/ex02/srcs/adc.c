/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:09:02 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 19:28:12 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <adc.h>




uint16_t ADC_read(uint8_t channel) {
    ADMUX = 0;  // Réinitialiser le registre ADMUX
    ADMUX = (1 << REFS0);  // AVCC comme référence, 10 bits (ADLAR = 0)
    ADMUX |= channel; //Sélection du canal ADC
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADSC);  // Démarrer conversion
    while (ADCSRA & (1 << ADSC));  // Attendre la fin
    return ADC;  // Retourner valeur 10 bits (ADCL + ADCH)
}