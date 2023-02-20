/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:16:28 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 04:33:53 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		return (ft_putstr_fd("Syntax Error: too few or too many arguments\n"\
								, 2), 1);
	data = (t_data){0};
	if (init_map(ft_strdup(argv[1]), &data.map))
		return (1);
	if (initialize(&data))
	{
		free_allocated(&data);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(data.mlx_data.mlx, &hooks, &data);
	mlx_loop(data.mlx_data.mlx);
	free_allocated(&data);
	mlx_terminate(data.mlx_data.mlx);
	return (EXIT_SUCCESS);
}
