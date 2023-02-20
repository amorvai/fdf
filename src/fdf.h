/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:59:53 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 03:25:09 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42_Int.h"
# include "get_next_line/get_next_line_fd.h"
# include "printf/ft_printf.h"
# include <fcntl.h>
# include <math.h>

# define WIDTH 1024
# define HEIGHT 1024
# define ISO_X 35.264
# define ISO_Y 45
# define ISO_Z 0

typedef struct s_useful
{
	double	**translation;
	int		x_move;
	int		y_move;
	double	**scale;
	double	scale_factor;
	double	**rotation_x;
	double	rotation_x_factor;
	double	**rotation_y;
	double	rotation_y_factor;
	double	**rotation_z;
	double	rotation_z_factor;
	double	**ult;
	bool	height_color;
}				t_useful;

typedef struct s_mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx_data;

typedef struct s_point
{
	double		elevation;
	uint32_t	color;
	uint32_t	col_h;
	double		*projected;
	int			*pixel;
}				t_point;

typedef struct s_map
{
	t_point	**array;
	double	width;
	double	height;
}				t_map;

typedef struct s_data
{
	t_mlx_data	mlx_data;
	t_map		map;
	t_useful	useful;
}				t_data;

typedef struct s_draw
{
	int	dx;
	int	dy;
	int	zi;
	int	what;
	int	color_i;
}				t_draw;

//	 print_functions

void		print_map(t_map map);
// void		print_matrix(double **matrix);
// void		print_vector(double *vector);

//	 parsing

int			init_map(char *argv, t_map *map);

//	 parsing_utils

double		split_amount(char **splits);
void		remove_nl(char *line);
int			get_hex_number(char c);
uint32_t	hex_to_dec(char *hex);

//	 allocate / init_matrices

double		**alloc_matrix(void);

int			initialize(t_data *data);
int			init_t_points(t_data *data);

void		init_trans_m(t_data *data);
void		init_scale_m(t_data *data, double factor);
void		init_x_rotation_m(t_data *data, double rad);
void		init_y_rotation_m(t_data *data, double rad);
void		init_z_rotation_m(t_data *data, double rad);
// void		init_adjust_for_eye_coord(t_data *data);
// void		init_transform_m(t_data *data);

//	 free

void		free_allocated(t_data *data);
void		free_t_points(t_data *data, int max_y, int max_x, \
							bool projected_allocd);
void		free_map(t_map *map, int max_alloc);
void		free_matrix(double **matrix);

//	 calculate / matrix_calculations

void		calc_ult(t_data *data);
double		**matrix_matrix_mult(double **matrix1, double **matrix2, \
								double **result_m);
double		*matrix_vector_mult(double **matrix, double *vector, \
								double *result_v);

//	 hooks / change_matrices
void		hooks(void *param);
void		adjust_scale_m(t_data *data, int change);
void		adjust_height_m(t_data *data, int change);
void		adjust_x_rotation_m(t_data *data, int change);
void		adjust_y_rotation_m(t_data *data, int change);
void		adjust_z_rotation_m(t_data *data, int change);

//	 draw

void		draw(t_data *data);
void		draw_line(t_data *data, t_point *one, t_point *two);
uint32_t	get_color(uint32_t one, uint32_t two, double i, double d);
void		put_pixel(t_data *data, int x, int y, uint32_t color);
// void		draw_line(t_data *data, int *pixel_a, int *pixel_b);

//	 rgba

int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

#endif