#include "../cub3d.h"

char    *read_file(char *file, t_vars *vars)
{
	char buff[1024];

	vars->fd = open(file, O_RDONLY);
	if (vars->fd == -1)
		return (NULL);
	vars->ret = read(vars->fd, buff, 1023);
	while(vars->ret > 0)
	{
		buff[vars->ret] = '\0';
		vars->tmp = vars->line;
		vars->line = ft_strjoin(vars->line, buff);
		if(!vars->line)
		{
			free(vars->tmp);
			return (NULL);
		}
		free(vars->tmp);
		vars->ret = read(vars->fd, buff, 1023);
	}
	close(vars->fd);
	if (vars->ret == -1 || !vars->line)
		return (NULL);
	return (vars->line);
}

int	parse_elements(t_elements *elem, t_map *map, t_vars *vars)
{
	while (map->cmap[vars->i] && elem->all_parsed < 6)
	{
		if (only_spaces(map->cmap[vars->i]))
		{
			if(store_elem(elem, map->cmap[vars->i]) == 0)
				elem->all_parsed++;
			else
			{
				write(2, "Error: Invalid/Missing element\n", 32);
				return (0);
			}
		}
		vars->i++;
	}
	if (elem->all_parsed < 6)
	{
		write(2, "Error: Missing elements\n", 25);
		return (0);
	}
	while(map->cmap[vars->i])
	{
		if (!only_spaces(map->cmap[vars->i]))
		{
			vars->i++;
			continue;
		}
		else
			break;
	}
	map->map = &map->cmap[vars->i];
	return (1);
}



int parse_elem_map(char *file, t_data *data)
{
	t_map *map;
	t_elements *elements;
	t_vars vars;

	init_vars(&vars);
	map = &data->map;
	elements = &data->elements;
	map->fullcub = read_file(file, &vars);
	if (!map->fullcub)
		return (1);
	map->cmap = ft_split(map->fullcub, '\n');
	if (!map->cmap)
		return (1);
	free_str(&map->fullcub);
	init_vars(&vars);
	if(!parse_elements(elements, map, &vars))
		return (1);
	if (!validate_map(map, data))
		return (1);
	printf("NO: %s\n", elements->no);
	printf("SO: %s\n", elements->so);
	printf("WE: %s\n", elements->we);
	printf("EA: %s\n", elements->ea);
	printf("F: %d\n", elements->floor);
	printf("C: %d\n", elements->ceiling);
	
	while (map->map[vars.j])
	{
		printf("%s\n", map->map[vars.j]);
		vars.j++;
	}
	return (0);
}
