/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:16:58 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 03:13:40 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

double	**alloc_matrix(void)
{
	double	**matrix;
	int		i;

	matrix = ft_calloc(4, sizeof(double *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		matrix[i] = ft_calloc(4, sizeof(double));
		i++;
	}
	if (!matrix[0] || !matrix[1] || !matrix[2] || !matrix[3])
	{
		while (i >= 0)
		{
			if (matrix[i])
				free(matrix[i]);
			i--;
		}
		free(matrix);
		return (NULL);
	}
	return (matrix);
}

static int	assign_points(t_data *data, int y, int x, double *temp)
{
	data->map.array[y][x].projected = ft_calloc(4, sizeof(double));
	if (!data->map.array[y][x].projected)
	{
		ft_putstr_fd("Error: \
(init_t_points/assign_points) ft_calloc(projected)\n", 2);
		free_t_points(data, y, x, false);
		return (1);
	}
	data->map.array[y][x].pixel = ft_calloc(2, sizeof(int));
	if (!data->map.array[y][x].pixel)
	{
		ft_putstr_fd("Error: \
(init_t_points/assign_points) ft_calloc(pixel)\n", 2);
		free_t_points(data, y, x, true);
		return (1);
	}
	matrix_vector_mult(data->useful.ult, temp, data->map.array[y][x].projected);
	data->map.array[y][x].col_h = (int)((double)0xFFFFFF - \
		(double)0xFFFFFF * (data->map.array[y][x].elevation / 100)) \
															<< 8 | 0xFF;
	return (0);
}

int	init_t_points(t_data *data)
{
	int		y;
	int		x;
	double	*temp;

	temp = ft_calloc(4, sizeof(double));
	if (!temp)
		return (ft_putstr_fd("Error: (init_t_points) ft_calloc()\n", 2), 1);
	y = 0;
	temp[3] = 1;
	while (y < (int)data->map.height)
	{
		x = 0;
		temp[2] = (double)y;
		while (x < (int)data->map.width)
		{
			temp[0] = (double)x;
			temp[1] = data->map.array[y][x].elevation;
			if (assign_points(data, y, x, temp))
				return (free(temp), 1);
			x++;
		}
		y++;
	}
	free(temp);
	return (0);
}

void	calc_initial(t_data *data)
{
	double	diagonal;

	diagonal = sqrt(pow(data->map.height, 2) + pow(data->map.width, 2));
	if (WIDTH >= HEIGHT)
		data->useful.scale_factor = (HEIGHT / 2) / diagonal;
	else
		data->useful.scale_factor = (WIDTH / 2) / diagonal;
	data->useful.rotation_x_factor = ISO_X;
	data->useful.rotation_y_factor = ISO_Y;
	data->useful.rotation_z_factor = ISO_Z;
	init_trans_m(data);
	init_scale_m(data, data->useful.scale_factor);
	init_x_rotation_m(data, data->useful.rotation_x_factor);
	init_y_rotation_m(data, data->useful.rotation_y_factor);
	init_z_rotation_m(data, data->useful.rotation_z_factor);
	data->useful.ult = alloc_matrix();
}

int	initialize(t_data *data)
{
	calc_initial(data);
	calc_ult(data);
	if (init_t_points(data))
		return (1);
	data->mlx_data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	if (!data->mlx_data.mlx)
		return (ft_putstr_fd("mlx_init failure\n", 2), 1);
	data->mlx_data.img = mlx_new_image(data->mlx_data.mlx, WIDTH, HEIGHT);
	if (!data->mlx_data.img)
		return (ft_putstr_fd("img init failure\n", 2), 1);
	mlx_image_to_window(data->mlx_data.mlx, data->mlx_data.img, 0, 0);
	draw(data);
	return (0);
}
