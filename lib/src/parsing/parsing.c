/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:59:13 by amorvai           #+#    #+#             */
/*   Updated: 2022/11/27 02:51:50 by amorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
// #include <stdio.h>

static int	find_map_size(char *path, t_map *map)
{
	int		fd;
	char	*line;
	char	**splits;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error: (init_map/find_map_size) open()\n", 2), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_nl(line);
		splits = ft_split(line, ' ');
		free(line);
		if (splits == NULL)
			return (\
			ft_putstr_fd("Error: (init_map/find_map_size) ft_split()\n", 2), 1);
		if (map->width == 0)
			map->width = split_amount(splits);
		else if (map->width != split_amount(splits))
			return (ft_putstr_fd("Error: (init_map/find_map_size) \
inconsistent map size!\n", 2), free_splits(splits), 1);
		free_splits(splits);
		map->height += 1;
		line = get_next_line(fd);
	}
	return (0);
}

static int	parse_coordinates(t_map *map, char **splits, int z)
{
	int		x;
	int		value;
	char	**point_value;

	x = 0;
	while (splits[x] != NULL)
	{
		point_value = ft_split(splits[x], ',');
		if (point_value == NULL)
			return (ft_putstr_fd(\
			"Error: (init_map/parse/parse_coordinates) ft_split\n", 2), 1);
		if (!ft_atoi(point_value[0], &value))
			return (ft_putstr_fd(\
			"Error: (init_map/parse/parse_coordinat) ft_atoi\n", 2), \
			free_splits(point_value), 1);
		map->array[z][x].elevation = (double)value;
		if (point_value[1] != NULL)
			map->array[z][x].color = hex_to_dec(point_value[1]);
		else
			map->array[z][x].color = 0xffffffff;
		x++;
		free_splits(point_value);
	}
	return (0);
}
			// printf("not an int: |%s|\n", point_info[0]);

static int	parse_two(t_map *map, char *line, int fd)
{
	char	**splits;
	int		z;

	z = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_nl(line);
		splits = ft_split(line, ' ');
		free(line);
		if (splits == NULL)
			return (free_map(map, z), ft_putstr_fd(\
			"Error: (init_map/parse) ft_split\n", 2), 1);
		map->array[z] = ft_calloc(map->width, sizeof(t_point));
		if (parse_coordinates(map, splits, z))
			return (free_map(map, z + 1), free_splits(splits), 1);
		z++;
		free_splits(splits);
		line = get_next_line(fd);
	}
	return (0);
}
		// printf("parsing line %i...\n", z);

static int	parse(char *path, t_map *map)
{
	int		fd;

	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (ft_putstr_fd("Error: (init_map/parse) open()\n", 2), -1);
	if (parse_two(map, path, fd))
		return (1);
	return (0);
}

int	init_map(char *path, t_map *map)
{
	int	parse_return;

	map->width = 0;
	if (find_map_size(path, map))
		return (free(path), 1);
	map->array = ft_calloc((map->height + 1), sizeof(*map->array));
	if (map->array == NULL)
	{
		ft_putstr_fd("Error: (init_map) ft_calloc\n", 2);
		return (free(map->array), 1);
	}
	parse_return = parse(path, map);
	if (parse_return == -1)
		return (free(map->array), 1);
	else if (parse_return)
		return (1);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	data = (t_data){0};
// 	if (argc != 2)
// 		return (1);
// 	if (init_map(argv[1], &data.map))
// 		return (free_map(data.map), 1);
// 	print_map(data.map);
// 	free_map(data.map);
// 	// system("leaks fdf");
// 	return (0);
// }
//
//131	data = (t_data){0}; // sets all bytes to zero (recursively)
