/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:21:49 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:52:28 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_pixel(t_data *data, int x, int y, uint32_t color)
{
	x = x + (WIDTH / 2) + data->useful.x_move;
	y = y + (HEIGHT / 2) + data->useful.y_move;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	mlx_put_pixel(data->mlx_data.img, x, y, color);
}

uint32_t	get_color(uint32_t one, uint32_t two, double i, double d)
{
	double	r;
	double	g;
	double	b;
	double	a;

	if (i == 0 || one == two)
		return (one);
	if (i == d)
		return (two);
	r = get_r(one) * (1 - i / d) + get_r(two) * (i / d);
	g = get_g(one) * (1 - i / d) + get_g(two) * (i / d);
	b = get_b(one) * (1 - i / d) + get_b(two) * (i / d);
	a = get_a(one) * (1 - i / d) + get_a(two) * (i / d);
	return (get_rgba(r, g, b, a));
}

void	draw_backwards(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->map.height - 1;
	while (y >= 0)
	{
		x = (int)data->map.width - 1;
		while (x >= 0)
		{
			data->map.array[y][x].pixel[0] = \
							(int)((data->map.array[y][x].projected[0]) + 0.5);
			data->map.array[y][x].pixel[1] = \
							(int)((data->map.array[y][x].projected[1]) + 0.5);
			if (x != data->map.width - 1)
				draw_line(data, &data->map.array[y][x + 1], \
								&data->map.array[y][x]);
			if (y != data->map.height - 1)
				draw_line(data, &data->map.array[y + 1][x], \
								&data->map.array[y][x]);
			x--;
		}
		y--;
	}
}

void	draw_forwards(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)data->map.height)
	{
		x = 0;
		while (x < (int)data->map.width)
		{
			data->map.array[y][x].pixel[0] = \
							(int)((data->map.array[y][x].projected[0]) + 0.5);
			data->map.array[y][x].pixel[1] = \
							(int)((data->map.array[y][x].projected[1]) + 0.5);
			if (x > 0)
				draw_line(data, &data->map.array[y][x - 1], \
								&data->map.array[y][x]);
			if (y > 0)
				draw_line(data, &data->map.array[y - 1][x], \
								&data->map.array[y][x]);
			x++;
		}
		y++;
	}
}

void	draw(t_data *data)
{
	if (data->useful.rotation_y_factor > 90 \
		&& data->useful.rotation_y_factor < 270)
	{
		draw_backwards(data);
		return ;
	}
	draw_forwards(data);
}

// put_pixel(data, data->map.array[y][x].pixel[0],
// data->map.array[y][x].pixel[1], data->map.array[y][x].color);
// printf("data->useful.rotation_y_factor : %f\n",
// data->useful.rotation_y_factor);

// printf("y: %i\tx: %i\n", y, x);
// data->map.array[alpha][beta].color
