/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:03 by mshaheen          #+#    #+#             */
/*   Updated: 2025/03/01 03:17:19 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	store_map(t_map *map, int start)
{
	int	i;
	int	map_end;

	i = start;
	map_end = 0;
	map->rows = 0;
	while (map->cmap[i])
	{
		if (empty_line(map->cmap[i]))
			map_end = 1;
		else
		{
			if (map_end)
			{
				if (only_spaces(map->cmap[i]))
					return (err_msg("Error: Empty line in map\n"));
			}
			else
				map->rows++;
		}
		i++;
	}
	if (map->rows == 0)
		return (err_msg("Error: Empty map\n"));
	return (copy_map(map, start));
}

int	parse_elements(t_elements *elem, t_map *map, t_vars *vars)
{
	while (map->cmap[vars->i] && elem->all_parsed < 6)
	{
		if (only_spaces(map->cmap[vars->i]))
		{
			if (store_elem(elem, map->cmap[vars->i]) == 0)
				elem->all_parsed++;
			else
				return (err_msg("Error: Invalid/Missing element\n"));
		}
		vars->i++;
	}
	if (elem->all_parsed < 6)
		return (err_msg("Error: Missing elements\n"));
	while (map->cmap[vars->i] && !only_spaces(map->cmap[vars->i]))
		vars->i++;
	if (!store_map(map, vars->i))
		return (0);
	return (1);
}

int	get_file_size(char *file)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(file, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		return (0);
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (size);
}

int	read_file_array(char *file, t_map *map, t_vars var)
{
	int		fd;
	char	*line;

	init_vars(&var);
	fd = open(file, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		map->cmap[var.i] = line;
		var.i++;
		line = get_next_line(fd);
	}
	map->cmap[var.i] = NULL;
	close(fd);
	return (1);
}

int	parse_elem_map(char *file, t_data *data)
{
	t_map		*map;
	t_elements	*elements;
	t_vars		vars;
	int			size;
	int			check;

	init_vars(&vars);
	map = &data->map;
	elements = &data->elements;
	check = check_file(file);
	if (check == 0 || check == -2 || check == -1)
		return (file_error(check));
	size = get_file_size(file);
	if (size == 0 || size == -2 || size == -1)
		return (file_error(size));
	map->cmap = ft_calloc(size + 1, sizeof(char *));
	if (!map->cmap)
		return (err_msg("Error: Malloc\n"));
	if (!read_file_array(file, map, vars))
		return (err_msg("Error: Malloc\n"));
	if (!parse_elements(elements, map, &vars))
		return (0);
	if (!validate_map(map, data))
		return (0);
	return (1);
}
