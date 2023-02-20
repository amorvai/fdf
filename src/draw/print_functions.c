/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:48:27 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 03:16:31 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_map(t_map map)
{
	int	x;
	int	z;

	z = 0;
	ft_printf("map.height: %i\n", map.height);
	ft_printf("map.width: %i\n", map.width);
	while (z < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (x != 0)
				ft_printf("\t");
			ft_printf("%i", map.array[z][x].elevation);
			ft_printf(", %x", map.array[z][x].color);
			x++;
		}
		z++;
		ft_printf("\n\n");
	}
}

// void	print_matrix(double **matrix)
// {
// 	int	i;
// 	int	j;

// 	if (!matrix)
// 		return ;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		ft_printf("{ ");
// 		while (j < 4)
// 		{
// 			ft_printf("%lf\t", matrix[i][j]);
// 			j++;
// 		}
// 		ft_printf("}\n");
// 		i++;
// 	}
// }

// void	print_vector(double *vector)
// {
// 	int	j;

// 	if (!vector)
// 		return ;
// 	j = 0;
// 	ft_printf("{ ");
// 	while (j < 4)
// 	{
// 		ft_printf("%lf\t", vector[j]);
// 		j++;
// 	}
// 	ft_printf("}\n");
// }
