/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_matrices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:35:39 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:52:20 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	adjust_scale_m(t_data *data, int change)
{
	if (change == -1)
	{
		data->useful.scale[0][0] = data->useful.scale[0][0] / 1.1;
		data->useful.scale[1][1] = data->useful.scale[1][1] / 1.1;
		data->useful.scale[2][2] = data->useful.scale[2][2] / 1.1;
	}
	else if (change == 1)
	{
		data->useful.scale[0][0] = data->useful.scale[0][0] * 1.1;
		data->useful.scale[1][1] = data->useful.scale[1][1] * 1.1;
		data->useful.scale[2][2] = data->useful.scale[2][2] * 1.1;
	}
}

void	adjust_height_m(t_data *data, int change)
{
	if (change == -1)
		data->useful.scale[1][1] = data->useful.scale[1][1] / 1.1;
	if (change == 1)
		data->useful.scale[1][1] = data->useful.scale[1][1] * 1.1;
}

void	adjust_x_rotation_m(t_data *data, int change)
{
	double	rad;

	if (change == -1)
		data->useful.rotation_x_factor = data->useful.rotation_x_factor - 2;
	else if (change == 1)
		data->useful.rotation_x_factor = data->useful.rotation_x_factor + 2;
	if (data->useful.rotation_x_factor > 360)
		data->useful.rotation_x_factor = data->useful.rotation_x_factor - 360;
	if (data->useful.rotation_x_factor < 0)
		data->useful.rotation_x_factor = data->useful.rotation_x_factor + 360;
	rad = data->useful.rotation_x_factor / 180 * M_PI;
	data->useful.rotation_x[1][1] = cos(rad);
	data->useful.rotation_x[1][2] = sin(rad);
	data->useful.rotation_x[2][1] = -sin(rad);
	data->useful.rotation_x[2][2] = cos(rad);
}

void	adjust_y_rotation_m(t_data *data, int change)
{
	double	rad;

	if (change == -1)
		data->useful.rotation_y_factor = data->useful.rotation_y_factor - 2;
	else if (change == 1)
		data->useful.rotation_y_factor = data->useful.rotation_y_factor + 2;
	if (data->useful.rotation_y_factor > 360)
		data->useful.rotation_y_factor = data->useful.rotation_y_factor - 360;
	if (data->useful.rotation_y_factor < 0)
		data->useful.rotation_y_factor = data->useful.rotation_y_factor + 360;
	rad = data->useful.rotation_y_factor / 180 * M_PI;
	data->useful.rotation_y[0][0] = cos(rad);
	data->useful.rotation_y[0][2] = -sin(rad);
	data->useful.rotation_y[2][0] = sin(rad);
	data->useful.rotation_y[2][2] = cos(rad);
}

void	adjust_z_rotation_m(t_data *data, int change)
{
	double	rad;

	if (change == -1)
		data->useful.rotation_z_factor = data->useful.rotation_z_factor - 2;
	else if (change == 1)
		data->useful.rotation_z_factor = data->useful.rotation_z_factor + 2;
	if (data->useful.rotation_z_factor > 360)
		data->useful.rotation_z_factor = data->useful.rotation_z_factor - 360;
	if (data->useful.rotation_z_factor < 0)
		data->useful.rotation_z_factor = data->useful.rotation_z_factor + 360;
	rad = data->useful.rotation_z_factor / 180 * M_PI;
	data->useful.rotation_z[0][0] = cos(rad);
	data->useful.rotation_z[0][1] = -sin(rad);
	data->useful.rotation_z[1][0] = sin(rad);
	data->useful.rotation_z[1][1] = cos(rad);
}
