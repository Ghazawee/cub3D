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
		if(map->map[i][vars.j] == '\0')
		{
			i++;
			continue;
		}
		if (map->map[i][vars.j] != '1') // check if just spaces then dont throw error ??
			return (err_msg("Error: Maper is not closed\n"));
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
	if ((j + 1 < (int)(ft_strlen(map->map[i])) && map->map[i][j + 1] && map->map[i][j + 1] != '1' 
	&& map->map[i][j + 1] != ' ') || (j > 0 && map->map[i][j - 1] && 
	map->map[i][j - 1] != '1' && map->map[i][j - 1] != ' ')
	|| (i + 1< (map->rows) && j < (int)ft_strlen(map->map[i + 1]) && map->map[i + 1] && map->map[i + 1][j] != '1' 
	&& map->map[i + 1][j] != ' ') || (i > 0 && j < (int)ft_strlen(map->map[i - 1]) && map->map[i - 1] && 
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
		while (map->map[i][j]) // maybe dont check last row as well
		{
			
			if (map->map[i][j] == ' ') // can check if its within the column before calling the function
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
int check_neighbours(t_map *map, int i, int j)
{
	int rlen;

	rlen = (int)ft_strlen(map->map[i]);
	if(i <= 0 || i >= map->rows - 1 || j <= 0 || j >= rlen -1)
		return (0);
	if(j + 1 >= rlen || map->map[i][j+1] == '\0' ||  map->map[i][j+1] == ' ')
		return (0);
	if (j - 1 < 0 || map->map[i][j - 1] == '\0' || map->map[i][j - 1] == ' ')
		return (0);
	if (i + 1 >= map->rows || j >= (int)ft_strlen(map->map[i+1]) || map->map[i + 1][j] == '\0' || map->map[i + 1][j] == ' ')
		return (0);
	if (i - 1 < 0 || j >= (int)ft_strlen(map->map[i - 1]) || map->map[i -1][j] == '\0' || map->map[i -1][j] == ' ')
		return (0);
	return (1);
}

int valid_zero_player(t_map *map)
{
	int i;
	int j;

	i = 1;
	while(i < map->rows -1)
	{
		j = 1;
		while(j < (int)ft_strlen(map->map[i]) - 1)
		{
			if(map->map[i][j] == '0')
			{
				if(!check_neighbours(map, i, j))
					return(err_msg("Error: Floor not enclosed\n"));
			}
			else if(map->map[i][j] == map->direction)
			{
				if(!check_neighbours(map, i, j))
					return(err_msg("Error: Player not enclosed\n"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

void calculate_map_cols(t_map *map)
{
	int i;
	int len;
	int max;

	i = 0;
	max = 0;
	while(map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	map->cols = max;
}

int	validate_map(t_map *map, t_data *data)
{
	t_vars vars;
	(void) data;

	init_vars(&vars);
	if (!validate_map_chars(map, vars))
		return (0);
	calculate_map_rows(map);
	calculate_map_cols(map);
	if (!validate_map_walls(map, vars) || !validate_spaces(map) || !valid_zero_player(map)) // need to also check if 0 is closed by 1's like yousef said or stop validating spaces just validate 0 because it started giving invalid reads or do padding like tariq said
		return (0);
	return (1);
}