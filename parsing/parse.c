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

int empty_line(char *str)
{
	// while(*str)
	// {
		if(*str == '\n')
			str++;
	// }
	if (*str == '\0')
		return (0);
	return (1);
}

int	store_map(t_map *map, int start)
{
	int i;
	int j;

	i = start;
	map->rows = 0;
	while(map->cmap[i])
	{
		if(!empty_line(map->cmap[i]))
			return (err_msg("Error: Empty line in map\n"));
		else
			map->rows++;
		i++;
	}
	if (map->rows == 0)
		return (err_msg("Error: Empty map\n"));
	map->map = ft_calloc(map->rows + 1, sizeof(char *));
	if(!map->map)
		return (err_msg("Error: Malloc\n"));
	i = start;
	j = 0;
	while(map->cmap[i])
	{
		map->map[j] = ft_strtrim(map->cmap[i], "\n");
		if(!map->map[j])
		{
			while(j >= 0)
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

int	parse_elements(t_elements *elem, t_map *map, t_vars *vars)
{
	while (map->cmap[vars->i] && elem->all_parsed < 6)
	{
		if (only_spaces(map->cmap[vars->i]))
		{
			if(store_elem(elem, map->cmap[vars->i]) == 0)
				elem->all_parsed++;
			else
				return (err_msg("Error: Invalid/Missing element\n"));
		}
		vars->i++;
	}
	if (elem->all_parsed < 6)
		return (err_msg("Error: Missing elements\n"));
	while(map->cmap[vars->i] && !only_spaces(map->cmap[vars->i]))
		vars->i++;
	if(!store_map(map, vars->i))
		return (0);
	return (1);
}

int get_file_size(char *file)
{
	int fd;
	// int ret;
	char *line;
	int size;

	fd = open(file, O_RDONLY);
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
int read_file_array(char *file, t_map *map, t_vars var)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while(line)
	{
		map->cmap[var.i] = line;
		var.i++;
		line = get_next_line(fd);
	}
	map->cmap[var.i] = NULL;
	close(fd);
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
	int size = get_file_size(file);
	if(size <= 0)
		return (err_msg("Error: File not found||Empty\n"));
	map->cmap = ft_calloc(size + 1, sizeof(char *));
	if (!map->cmap)
		return (err_msg("Error: Malloc\n"));
	if (!read_file_array(file, map, vars))
		return (err_msg("Error: Malloc\n"));
	init_vars(&vars);
	if(!parse_elements(elements, map, &vars))
		return (0);
	if (!validate_map(map, data))
		return (0);
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
	return (1);
}
