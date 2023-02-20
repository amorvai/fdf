/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:38:37 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:52:08 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//	TRANSLATION	MATRIX
//	{	1	0	0	offset_x	}
//	{	0	1	0	offset_y	}
//	{	0	0	1		0		}
//	{	0	0	0		1		}
//	--------------------------------------------------------
//	offset calculated automatically in accordance to the map
void	init_trans_m(t_data *data)
{
	double	offset_y;
	double	offset_x;

	offset_x = data->map.width / -2;
	offset_y = data->map.height / -2;
	data->useful.translation = alloc_matrix();
	data->useful.translation[0][0] = 1;
	data->useful.translation[0][3] = offset_x;
	data->useful.translation[1][1] = 1;
	data->useful.translation[2][2] = 1;
	data->useful.translation[2][3] = offset_y;
	data->useful.translation[3][3] = 1;
}

//
//	SCALE	MATRIX
//	{	fact	0		0		0	}
//	{	0		-fact	0		0	}
//	{	0		0		fact	0	}
//	{	0		0		0		1	}
//	-----------------------------------
void	init_scale_m(t_data *data, double factor)
{
	data->useful.scale = alloc_matrix();
	data->useful.scale[0][0] = factor;
	data->useful.scale[1][1] = -factor;
	data->useful.scale[2][2] = factor;
	data->useful.scale[3][3] = 1;
}

//
//	ROTATION_X	MATRIX
//	{	1		0			0		0	}
//	{	0	cos(rad)	sin(rad)	0	}
//	{	0	-sin(rad)	cos(rad)	0	}
//	{	0		0			0		1	}
//	--------------------------------------
void	init_x_rotation_m(t_data *data, double degree)
{
	double	rad;

	rad = degree / 180 * M_PI;
	data->useful.rotation_x = alloc_matrix();
	data->useful.rotation_x[0][0] = 1;
	data->useful.rotation_x[1][1] = cos(rad);
	data->useful.rotation_x[1][2] = sin(rad);
	data->useful.rotation_x[2][1] = -sin(rad);
	data->useful.rotation_x[2][2] = cos(rad);
	data->useful.rotation_x[3][3] = 1;
}

//
//	ROTATION_X	MATRIX
//	{	cos(rad)	0	-sin(rad)	0	}
//	{		0		1		0		0	}
//	{	sin(rad)	0	cos(rad)	0	}
//	{		0		0		0		1	}
//	--------------------------------------
void	init_y_rotation_m(t_data *data, double degree)
{
	double	rad;

	rad = degree / 180 * M_PI;
	data->useful.rotation_y = alloc_matrix();
	data->useful.rotation_y[0][0] = cos(rad);
	data->useful.rotation_y[0][2] = -sin(rad);
	data->useful.rotation_y[1][1] = 1;
	data->useful.rotation_y[2][0] = sin(rad);
	data->useful.rotation_y[2][2] = cos(rad);
	data->useful.rotation_y[3][3] = 1;
}

//
//	ROTATION_X	MATRIX
//	{	cos(rad)	-sin(rad)	0	0	}
//	{	sin(rad)	cos(rad)	0	0	}
//	{		0			0		1	0	}
//	{		0			0		0	1	}
//	---------------------------------------
void	init_z_rotation_m(t_data *data, double degree)
{
	double	rad;

	rad = degree / 180 * M_PI;
	data->useful.rotation_z = alloc_matrix();
	data->useful.rotation_z[0][0] = cos(rad);
	data->useful.rotation_z[0][1] = -sin(rad);
	data->useful.rotation_z[1][0] = sin(rad);
	data->useful.rotation_z[1][1] = cos(rad);
	data->useful.rotation_z[2][2] = 1;
	data->useful.rotation_z[3][3] = 1;
}

// void	init_adjust_for_eye_coord(t_data *data)
// {
// 	data->useful.eye_coord_translation = alloc_matrix();
// 	data->useful.eye_coord_translation[0][0] = 1;
// 	data->useful.eye_coord_translation[0][1] = 0;
// 	data->useful.eye_coord_translation[0][2] = 0;
// 	data->useful.eye_coord_translation[0][3] = 0;
// 	data->useful.eye_coord_translation[1][0] = 0;
// 	data->useful.eye_coord_translation[1][1] = 1;
// 	data->useful.eye_coord_translation[1][2] = 0;
// 	data->useful.eye_coord_translation[1][3] = 0;
// 	data->useful.eye_coord_translation[2][0] = 0;
// 	data->useful.eye_coord_translation[2][1] = 0;
// 	data->useful.eye_coord_translation[2][2] = 1;
// 	data->useful.eye_coord_translation[2][3] = 0;
// 	data->useful.eye_coord_translation[3][0] = 0;
// 	data->useful.eye_coord_translation[3][1] = 0;
// 	data->useful.eye_coord_translation[3][2] = 0;
// 	data->useful.eye_coord_translation[3][3] = 1;
// }

//	TRANFORMATION MATRIX
//	http://www.songho.ca/opengl/gl_projectionmatrix.html
//	
//	{	1/r		0			0			0	}
//	{	0		1/t			0			0	}
//	{	0		0		-2/(far-near)	0	}
//	{	0		0	-(f + n)/(f - n)	1	}
// 
// void	init_transform_m(t_data *data)
// {
// 	double	r;
// 	double	t;
// 	double	far;
// 	double	near;

// 	r = 1;
// 	t = 1;
// 	near = -3;
// 	far = -6;
// 	data->useful.transformation = alloc_matrix();
// 	data->useful.transformation[0][0] = 1 / r;
// 	data->useful.transformation[1][1] = 1 / t;
// 	data->useful.transformation[2][2] = -far / (far - near);
// 	data->useful.transformation[2][3] = -1;
// 	data->useful.transformation[3][2] = -(far * near) / (far - near);
// 	data->useful.transformation[3][3] = 0;
// }
//		DISLAIMER: we didnt get it to work
