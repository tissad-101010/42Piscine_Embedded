/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tissad <tissad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:04:26 by tissad            #+#    #+#             */
/*   Updated: 2025/03/13 15:09:54 by tissad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <uart.h>

// ft_strlen
static uint16_t ft_strlen(const char *s)
{
	uint32_t i = 0;
	while (s[i])
		i++;
	return (i);
}

// Function to convert an positive 16 bits integer to a string in a given base 
// The base must be between 2 and 16
// The string is stored in the buffer

// recursive subfunction
void itoa_base_rec(uint16_t value, char *buffer, char *base, int base_len, int *i)
{
	if (value == 0)
		return;

	itoa_base_rec(value / base_len, buffer, base, base_len, i);
	buffer[(*i)++] = base[value % base_len];
}

void itoa_base(uint16_t value, char *buffer, char *base)
{
	int i = 0;
	int base_len = ft_strlen(base);
	if (base_len < 2 || base_len > 16)
	{
		buffer[0] = '\0';
		return;
	}
	if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return;
	}
	itoa_base_rec(value, buffer, base, base_len, &i);
	buffer[i] = '\0';
}

// #include <stdlib.h>
// #include <stdio.h>
// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 	{
// 		return (1);
// 	}
// 	char buffer[17];
// 	itoa_base(atoi(av[1]), buffer, HEXA);
// 	printf("HEXA: %s\n", buffer);
// 	itoa_base(atoi(av[1]), buffer, BINARY);
// 	printf("BINARY: %s\n", buffer);
// 	itoa_base(atoi(av[1]), buffer, OCTAL);
// 	printf("OCTAL: %s\n", buffer);
// 	itoa_base(atoi(av[1]), buffer, DECIMAL);
// 	printf("DECIMAL: %s\n", buffer);
// }