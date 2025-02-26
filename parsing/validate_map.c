/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:21 by mshaheen          #+#    #+#             */
/*   Updated: 2025/02/26 21:43:22 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_space(t_map *map, int i, int j)
{
	if ((j + 1 < (int)(ft_strlen(map->map[i])) && map->map[i][j + 1]
	&& map->map[i][j + 1] != '1' && map->map[i][j + 1] != ' ')
	|| (j > 0 && map->map[i][j - 1] && map->map[i][j - 1] != '1'
	&& map->map[i][j - 1] != ' ') ||
	(i + 1 < (map->rows) && j < (int)ft_strlen(map->map[i + 1])
	&& map->map[i + 1] && map->map[i + 1][j] != '1'
	&& map->map[i + 1][j] != ' ') ||
	(i > 0 && j < (int)ft_strlen(map->map[i - 1]) && map->map[i - 1] &&
	map->map[i - 1][j] != '1' && map->map[i - 1][j] != ' '))
		return (0);
	return (1);
}

int	validate_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (map->map[i])
	{
		j = 1;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
			{
				if (!check_map_space(map, i, j))
					return (err_msg("Error: Space is not closed\n"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_neighbours(t_map *map, int i, int j)
{
	int	rlen;

	rlen = (int)ft_strlen(map->map[i]);
	if (i <= 0 || i >= map->rows - 1 || j <= 0 || j >= rlen - 1)
		return (0);
	if (j + 1 >= rlen || map->map[i][j + 1] == '\0'
		|| map->map[i][j + 1] == ' ')
		return (0);
	if (j - 1 < 0 || map->map[i][j - 1] == '\0' || map->map[i][j - 1] == ' ')
		return (0);
	if (i + 1 >= map->rows || j >= (int)ft_strlen(map->map[i + 1])
		|| map->map[i + 1][j] == '\0' || map->map[i + 1][j] == ' ')
		return (0);
	if (i - 1 < 0 || j >= (int)ft_strlen(map->map[i - 1])
		|| map->map[i - 1][j] == '\0' || map->map[i - 1][j] == ' ')
		return (0);
	return (1);
}

int	valid_zero_player(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->rows -1)
	{
		j = 1;
		while (j < (int)ft_strlen(map->map[i]) - 1)
		{
			if (map->map[i][j] == '0')
			{
				if (!check_neighbours(map, i, j))
					return (err_msg("Error: Floor not enclosed\n"));
			}
			else if (map->map[i][j] == map->direction)
			{
				if (!check_neighbours(map, i, j))
					return (err_msg("Error: Player not enclosed\n"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_map *map, t_data *data)
{
	t_vars	vars;

	(void) data;
	init_vars(&vars);
	if (!validate_map_chars(map, vars))
		return (0);
	calculate_map_rows(map);
	init_vars(&vars);
	if (!validate_map_walls(map, vars) || !validate_spaces(map)
		|| !valid_zero_player(map))
		return (0);
	return (1);
}
