#include "../cub3d.h"

int	validate_map_chars(t_map *map, t_vars vars)
{
	while (map->map[vars.i])
	{
		vars.j = 0;
		while (map->map[vars.i][vars.j])
		{
			if(ft_strchr("01NSEW ", map->map[vars.i][vars.j]) == NULL)
				return(err_msg("Error: Invalid character in map\n"));
			if (ft_strchr("NSEW", map->map[vars.i][vars.j]))
			{
				if (vars.k)
					return(err_msg("Error: Multiple players\n"));
				map->p_x = vars.i;
				map->p_y = vars.j;
				map->direction = map->map[vars.i][vars.j];
				vars.k++;
			}
			vars.j++;
		}
		vars.i++;
	}
	if (!vars.k)
		return(err_msg("Error: No player\n"));
	return (1);
}

int validate_map_walls(t_map *map, t_vars vars)
{
	int i;
	
	init_vars(&vars);
	i = 1;
	if(!top_bot_row(map->map[0]) || !top_bot_row(map->map[map->rows - 1]))
		return (err_msg("Error: Map is not closed\n"));
	while(i <map->rows -1)
	{
		vars.k = ft_strlen(map->map[i]);
		vars.j = 0;
		while(map->map[i][vars.j] == ' ')
			vars.j++;
		if (map->map[i][vars.j] != '1')
			return (err_msg("Error: Map is not closed\n"));
		vars.j = vars.k - 1;
		while(vars.j >= 0 && map->map[i][vars.j] == ' ')
			vars.j--;
		if (map->map[i][vars.j] != '1')
			return (err_msg("Error: Mapy is not closed\n"));
		i++;
	}
	return (1);
}

int	check_map_space(t_map *map, int i, int j)
{
	if ((map->map[i][j + 1] && map->map[i][j + 1] != '1' 
	&& map->map[i][j + 1] != ' ') || (map->map[i][j - 1] && 
	map->map[i][j - 1] != '1' && map->map[i][j - 1] != ' ')
	|| (map->map[i + 1] && map->map[i + 1][j] != '1' 
	&& map->map[i + 1][j] != ' ') || (map->map[i - 1] && 
	map->map[i - 1][j] != '1' && map->map[i - 1][j] != ' '))
		return (0);
	return (1);
}

int validate_spaces(t_map *map)
{
	int i;
	int j;

	i = 1;
	while (map->map[i])
	{
		j = 1;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
			{
				if(!check_map_space(map, i, j))
					return (err_msg("Error: Space is not closed\n"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_map *map, t_data *data)
{
	t_vars vars;
	(void) data;

	init_vars(&vars);
	if (!validate_map_chars(map, vars))
		return (0);
	calculate_map_rows(map);
	if (!validate_map_walls(map, vars) || !validate_spaces(map))
		return (0);
	return (1);
}