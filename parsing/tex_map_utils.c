/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:16 by mshaheen          #+#    #+#             */
/*   Updated: 2025/02/26 21:43:17 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	copy_map(t_map *map, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (map->cmap[i] && j < map->rows)
	{
		map->map[j] = ft_strtrim(map->cmap[i], "\n");
		if (!map->map[j])
		{
			while (j >= 0)
			{
				free_str(&map->map[j]);
				j--;
			}
			return (err_msg("Error: Malloc\n"));
		}
		i++;
		j++;
	}
	map->map[j] = NULL;
	return (1);
}

int	assign_tex(char **tex, char *trim)
{
	if (*tex)
		return (1);
	*tex = ft_strdup(trim);
	if (*tex)
		return (0);
	return (1);
}
