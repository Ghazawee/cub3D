#include "../cub3d.h"

void calculate_map_rows(t_map *map)
{
	int i;

	i = 0;
	while (map->map[i])
		i++;
	map->rows = i;
}

int top_bot_row(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}
