/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:26 by mshaheen          #+#    #+#             */
/*   Updated: 2025/02/26 21:43:27 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	empty_line(char *str)
{
	if (*str == '\n')
		str++;
	return (*str == '\0');
}

void	calculate_map_rows(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		i++;
	map->rows = i;
}

int	top_bot_row(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	validate_map_chars(t_map *map, t_vars vars)
{
	while (map->map[vars.i])
	{
		vars.j = 0;
		while (map->map[vars.i][vars.j])
		{
			if (ft_strchr("01NSEW ", map->map[vars.i][vars.j]) == NULL)
				return (err_msg("Error: Invalid character in map\n"));
			if (ft_strchr("NSEW", map->map[vars.i][vars.j]))
			{
				if (vars.k)
					return (err_msg("Error: Multiple players\n"));
				map->p_x = vars.j;
				map->p_y = vars.i;
				map->direction = map->map[vars.i][vars.j];
				vars.k++;
			}
			vars.j++;
		}
		vars.i++;
	}
	if (!vars.k)
		return (err_msg("Error: No player\n"));
	return (1);
}

int	validate_map_walls(t_map *map, t_vars vars)
{
	int	i;

	i = 0;
	if (!top_bot_row(map->map[0]) || !top_bot_row(map->map[map->rows - 1]))
		return (err_msg("Error: Border is not closed\n"));
	while (++i < map->rows -1)
	{
		vars.k = ft_strlen(map->map[i]);
		vars.j = 0;
		while (map->map[i][vars.j] == ' ')
			vars.j++;
		if (map->map[i][vars.j] == '\0')
		{
			i++;
			continue ;
		}
		if (map->map[i][vars.j] != '1')
			return (err_msg("Error: Right border is not closed\n"));
		vars.j = vars.k - 1;
		while (vars.j >= 0 && map->map[i][vars.j] == ' ')
			vars.j--;
		if (map->map[i][vars.j] != '1')
			return (err_msg("Error: Left border is not closed\n"));
	}
	return (1);
}
