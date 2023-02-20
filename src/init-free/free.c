/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:40:37 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:52:11 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_allocated(t_data *data)
{
	if (data->map.array[0][0].projected)
		free_t_points(data, data->map.height, 0, false);
	free_map(&data->map, data->map.height);
	free_matrix(data->useful.translation);
	free_matrix(data->useful.scale);
	free_matrix(data->useful.rotation_x);
	free_matrix(data->useful.rotation_y);
	free_matrix(data->useful.rotation_z);
	free_matrix(data->useful.ult);
	if (data->mlx_data.img)
		mlx_delete_image(data->mlx_data.mlx, data->mlx_data.img);
}

void	free_matrix(double **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (i < 4)
		{
			if (matrix[i])
				free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

//pass map.height as max_alloc, when used outside of parsing
void	free_map(t_map *map, int max_alloc)
{
	int	y;

	y = 0;
	if (map->array != NULL)
	{
		while (y < max_alloc)
		{
			if (map->array[y])
				free(map->array[y]);
			y++;
		}
		free(map->array);
	}
}

// when used outside of parsing
// ----------------------------
// pass	map.height	as max_y
//	&	0			as max_x
//	&	false		as bool
void	free_t_points(t_data *data, int max_y, int max_x, bool projected_allocd)
{
	int	y;
	int	x;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < data->map.width)
		{
			free(data->map.array[y][x].projected);
			free(data->map.array[y][x].pixel);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < max_x)
	{
		free(data->map.array[y][x].projected);
		free(data->map.array[y][x].pixel);
		x++;
	}
	if (projected_allocd)
		free(data->map.array[y][x].projected);
}
