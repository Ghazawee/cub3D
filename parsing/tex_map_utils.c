/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:16 by mshaheen          #+#    #+#             */
/*   Updated: 2025/03/01 03:14:46 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	copy_map(t_map *map, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	map->map = ft_calloc(map->rows + 1, sizeof(char *));
	if (!map->map)
		return (err_msg("Error: Malloc\n"));
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

int	check_file(char *file)
{
	int		fd;
	int		total_bytes;
	int		bytes_read;
	char	buffer[4096];

	fd = open(file, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		return (-2);
	total_bytes = 0;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		total_bytes += bytes_read;
		if (total_bytes > MAX_BYTES)
			return (close(fd), -1);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	if (bytes_read < 0)
		return (-2);
	if (total_bytes == 0)
		return (0);
	return (1);
}
