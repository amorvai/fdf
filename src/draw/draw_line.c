/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:05:23 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 03:23:47 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_line_low_2(t_data *data, t_point *one, t_point *two, t_draw *vars)
{
	int		first[2];
	int		second[2];

	first[0] = one->pixel[0];
	first[1] = one->pixel[1];
	second[0] = two->pixel[0];
	second[1] = two->pixel[1];
	while (first[0] <= second[0])
	{
		if (data->useful.height_color)
			put_pixel(data, first[0], first[1], \
			get_color(one->col_h, two->col_h, vars->color_i, (double)vars->dx));
		else
			put_pixel(data, first[0], first[1], \
			get_color(one->color, two->color, vars->color_i, (double)vars->dx));
		if (vars->what > 0)
		{
			first[1] = first[1] + vars->zi;
			vars->what = vars->what + (2 * (vars->dy - vars->dx));
		}
		else
			vars->what = vars->what + (2 * vars->dy);
		first[0]++;
		vars->color_i++;
	}
}

void	draw_line_low(t_data *data, t_point *one, t_point *two)
{
	t_draw	vars;

	vars.color_i = 0;
	vars.dx = two->pixel[0] - one->pixel[0];
	vars.dy = two->pixel[1] - one->pixel[1];
	vars.zi = 1;
	if (vars.dy < 0)
	{
		vars.zi = -1;
		vars.dy = -vars.dy;
	}
	vars.what = (2 * vars.dy) - vars.dx;
	draw_line_low_2(data, one, two, &vars);
}

void	draw_line_high_2(t_data *data, t_point *one, t_point *two, t_draw *vars)
{
	int	first[2];
	int	second[2];

	first[0] = one->pixel[0];
	first[1] = one->pixel[1];
	second[0] = two->pixel[0];
	second[1] = two->pixel[1];
	while (first[1] <= second[1])
	{
		if (data->useful.height_color)
			put_pixel(data, first[0], first[1], \
			get_color(one->col_h, two->col_h, vars->color_i, (double)vars->dy));
		else
			put_pixel(data, first[0], first[1], \
			get_color(one->color, two->color, vars->color_i, (double)vars->dy));
		if (vars->what > 0)
		{
			first[0] = first[0] + vars->zi;
			vars->what = vars->what + (2 * (vars->dx - vars->dy));
		}
		else
			vars->what = vars->what + (2 * vars->dx);
		first[1]++;
		vars->color_i++;
	}
}

void	draw_line_high(t_data *data, t_point *one, t_point *two)
{
	t_draw	vars;

	vars.color_i = 0;
	vars.dx = two->pixel[0] - one->pixel[0];
	vars.dy = two->pixel[1] - one->pixel[1];
	vars.zi = 1;
	if (vars.dx < 0)
	{
		vars.zi = -1;
		vars.dx = -vars.dx;
	}
	vars.what = (2 * vars.dx) - vars.dy;
	draw_line_high_2(data, one, two, &vars);
}

void	draw_line(t_data *data, t_point *one, t_point *two)
{
	if (fabs((double)(two->pixel[1] - one->pixel[1])) \
		< fabs((double)(two->pixel[0] - one->pixel[0])))
	{
		if (one->pixel[0] > two->pixel[0])
			draw_line_low(data, two, one);
		else
			draw_line_low(data, one, two);
	}
	else
	{
		if (one->pixel[1] > two->pixel[1])
			draw_line_high(data, two, one);
		else
			draw_line_high(data, one, two);
	}
}
