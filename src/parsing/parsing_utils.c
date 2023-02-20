/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:46:32 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:51:53 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>
#define HEXDIGITSUPPER "0123456789ABCDEF"
#define HEXDIGITSLOWER "0123456789abcdef"

double	split_amount(char **splits)
{
	int	number;

	number = 0;
	while (splits && splits[number] != NULL)
		number++;
	return ((double)number);
}

void	remove_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

int	get_hex_number(char c)
{
	int		i;

	i = 0;
	while (HEXDIGITSLOWER[i] != '\0')
	{
		if (c == HEXDIGITSLOWER[i] || c == HEXDIGITSUPPER[i])
			return (i);
		i++;
	}
	return (-1);
}

uint32_t	hex_to_dec(char *hex)
{
	long	i;
	long	exp;
	long	hex_base;
	long	n;

	if (hex == NULL)
		return (0);
	if (hex[0] == '0' && hex[1] == 'x')
		hex += 2;
	i = ft_strlen(hex) + 1;
	if (i > 7)
		return (0);
	exp = 2;
	n = 255;
	while (i >= exp)
	{
		hex_base = (long)get_hex_number(hex[i - exp]);
		if (hex_base == -1)
			return (0);
		n = n + (hex_base * (long)pow(16, (double)exp));
		exp++;
		if (n > 4294967295)
			return (0);
	}
	return ((uint32_t) n);
}
// OLD		aka		does not add 0x000000FF for transparency channel
	// i = ft_strlen(hex) - 1;
	// if (i > 7)
	// 	return (0);
	// exp = 0;
	// n = 0;

//
	// 	printf("hex[i - exp]: %c\n", hex[i - exp]);
	// 	printf("x to the n (16^exp): %i;\texp: %ld\n", x_to_the_n(16, exp), exp);
		// printf("n: %ld\n", n);

// COVERED BY MATH.H POW()
//
// int	x_to_the_n(int x, int n)
// {
// 	int	result;

// 	if (n == 0)
// 		return (1);
// 	result = x;
// 	while (n > 1)
// 	{
// 		result = result * x;
// 		n--;
// 	}
// 	return (result);
// }
