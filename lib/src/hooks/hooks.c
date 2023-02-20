/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:36:08 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 04:30:47 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	calc_points(t_data *data)
{
	int		x;
	int		y;
	double	*temp;

	temp = ft_calloc(4, sizeof(double));
	if (!temp)
		return ;
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
			ft_bzero(data->map.array[y][x].projected, 4 * sizeof(double));
			matrix_vector_mult(data->useful.ult, temp, \
								data->map.array[y][x].projected);
			x++;
		}
		y++;
	}
	free(temp);
}

static void	reset_angles(t_data *data)
{
	double	rad;

	data->useful.rotation_x_factor = ISO_X;
	data->useful.rotation_y_factor = ISO_Y;
	data->useful.rotation_z_factor = ISO_Z;
	rad = data->useful.rotation_x_factor / 180 * M_PI;
	data->useful.rotation_x[1][1] = cos(rad);
	data->useful.rotation_x[1][2] = sin(rad);
	data->useful.rotation_x[2][1] = -sin(rad);
	data->useful.rotation_x[2][2] = cos(rad);
	rad = data->useful.rotation_y_factor / 180 * M_PI;
	data->useful.rotation_y[0][0] = cos(rad);
	data->useful.rotation_y[0][2] = -sin(rad);
	data->useful.rotation_y[2][0] = sin(rad);
	data->useful.rotation_y[2][2] = cos(rad);
	rad = data->useful.rotation_z_factor / 180 * M_PI;
	data->useful.rotation_z[0][0] = cos(rad);
	data->useful.rotation_z[0][1] = -sin(rad);
	data->useful.rotation_z[1][0] = sin(rad);
	data->useful.rotation_z[1][1] = cos(rad);
	data->useful.x_move = 0;
	data->useful.y_move = 0;
}

static void	hooks_tree(t_data *data, int change)
{
	if (change > 1)
	{
		calc_ult(data);
		calc_points(data);
		ft_bzero(data->mlx_data.img->pixels, \
					WIDTH * HEIGHT * sizeof(unsigned int));
		draw(data);
	}
}

static void	hooks_too(t_data *data, int change)
{
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_W) && change++)
		adjust_x_rotation_m(data, -1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_S) && change++)
		adjust_x_rotation_m(data, 1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_A) && change++)
		adjust_y_rotation_m(data, 1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_D) && change++)
		adjust_y_rotation_m(data, -1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_Q) && change++)
		adjust_z_rotation_m(data, 1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_E) && change++)
		adjust_z_rotation_m(data, -1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_RIGHT) && change++)
		data->useful.x_move += 4;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_LEFT) && change++)
		data->useful.x_move -= 4;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_UP) && change++)
		data->useful.y_move -= 4;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_DOWN) && change++)
		data->useful.y_move += 4;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_1) && change++)
		data->useful.height_color = false;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_2) && change++)
		data->useful.height_color = true;
	hooks_tree(data, change);
}

void	hooks(void *param)
{
	t_data	*data;
	int		change;

	data = (t_data *)param;
	change = 1;
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_ESCAPE))
	{
		free_allocated(data);
		mlx_terminate(data->mlx_data.mlx);
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_P) && change++)
		reset_angles(data);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_R) && change++)
		adjust_height_m(data, 1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_F) && change++)
		adjust_height_m(data, -1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_Z) && change++)
		adjust_scale_m(data, 1);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_C) && change++)
		adjust_scale_m(data, -1);
	hooks_too(data, change);
}
