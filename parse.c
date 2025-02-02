#include "cub3d.h"

void init_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->fd = -1;
	vars->ret = 0;
	vars->line = NULL;
	vars->tmp = NULL;
}
// char    *read_file(char *file, t_vars *vars)
// {
// 	char buff[1024];
// 	char *line;

// 	line = NULL;
// 	vars->fd = open(file, O_RDONLY);
// 	if (vars->fd == -1)
// 		return (NULL);
// 	vars->ret = read(vars->fd, buff, 1023);
// 	while(vars->ret > 0)
// 	{
// 		buff[vars->ret] = '\0';
// 		vars->tmp = line;
// 		line = ft_strjoin(line, buff);
// 		if(!line)
// 		{
// 			free(vars->tmp);
// 			return (NULL);
// 		}
// 		free(vars->tmp);
// 		vars->ret = read(vars->fd, buff, 1023);
// 	}
// 	close(vars->fd);
// 	if (vars->ret == -1 || !line)
// 		return (NULL);
// 	return (line);
// }

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

int	only_spaces(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

int parse_rgb(char *str)
{
	char **arr;
	int r;
	int g;
	int b;

	arr = ft_split(str, ',');
	if(!arr)
		return (-1);
	if(!arr[0] || !arr[1] || !arr[2] || arr[3])
	{
		fr_array(arr);
		return (-1);
	}
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	fr_array(arr);
	if(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int store_elem(t_elements *elem, char *line)
{
	char **arr;
	char *trim;

	arr = ft_split(line, ' ');
	if(!arr)
		return(1);
	if(!arr[0] || !arr[1] || arr[2])
	{
		fr_array(arr);
		return (1);
	}
	trim = ft_strtrim(arr[1], " ");
	if(!trim)
	{
		fr_array(arr);
		return (1);
	}
	if(ft_strncmp(arr[0], "NO", 3) == 0)
		elem->no = ft_strdup(trim);
	else if(ft_strncmp(arr[0], "SO", 3) == 0)
		elem->so = ft_strdup(trim);
	else if(ft_strncmp(arr[0], "WE", 3) == 0)
		elem->we = ft_strdup(trim);
	else if(ft_strncmp(arr[0], "EA", 3) == 0)
		elem->ea = ft_strdup(trim);
	else if(ft_strncmp(arr[0], "F", 2) == 0)
		elem->floor = parse_rgb(trim);
	else if(ft_strncmp(arr[0], "C", 2) == 0)
		elem->ceiling = parse_rgb(trim);
	else
		return (fr_array(arr), free(trim), 1);
	if(elem->floor == -1 || elem->ceiling == -1)
		return (fr_array(arr), free(trim), 1);
	fr_array(arr);
	free(trim);
	return (0);
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

void free_str(char **str)
{
    if (str && *str)
    {
        free(*str);
        *str = NULL;
    }
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
	// free(vars.line);
	if (!map->fullcub)
		return (1);
	map->cmap = ft_split(map->fullcub, '\n');
	if (!map->cmap)
		return (1);
	free_str(&map->fullcub);
	init_vars(&vars);
	if(!parse_elements(elements, map, &vars))
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
