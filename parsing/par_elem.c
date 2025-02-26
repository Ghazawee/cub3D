/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:43:13 by mshaheen          #+#    #+#             */
/*   Updated: 2025/02/26 21:43:14 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_color(char **str)
{
	char	*tmp;
	int		value;
	int		i;

	i = 0;
	tmp = *str;
	*str = ft_strtrim(*str, " \t\v\f\r");
	free(tmp);
	if (!*str)
		return (-1);
	tmp = *str;
	if (!*tmp)
		return (free_str(str), -1);
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]) == 0)
		{
			free_str(str);
			return (-1);
		}
		i++;
	}
	value = ft_atoi(*str);
	free_str(str);
	return (value);
}

int	parse_rgb(char *str)
{
	char	**arr;
	int		r;
	int		g;
	int		b;

	if (check_multiple_commas(str) == -1)
		return (-1);
	arr = ft_split(str, ',');
	if (!arr)
		return (-1);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3])
	{
		fr_array(arr);
		return (-1);
	}
	r = handle_color(&arr[0]);
	g = handle_color(&arr[1]);
	b = handle_color(&arr[2]);
	fr_array(arr);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int	store_tex(t_elements *elem, char *trim, char **arr)
{
	if (ft_strncmp(arr[0], "NO", 3) == 0)
		return (assign_tex(&elem->no, trim));
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
		return (assign_tex(&elem->so, trim));
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
		return (assign_tex(&elem->we, trim));
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
		return (assign_tex(&elem->ea, trim));
	return (0);
}

int	handle_tex(t_elements *elem, char *trim, char **arr)
{
	arr = ft_split(trim, ' ');
	if (!arr)
		return (1);
	if (!arr[0] || !arr[1] || arr[2])
	{
		free(trim);
		fr_array(arr);
		return (1);
	}
	free (trim);
	trim = ft_strtrim(arr[1], " \t\v\f\r");
	if (!trim)
	{
		fr_array(arr);
		return (1);
	}
	if (store_tex(elem, trim, arr))
	{
		free(trim);
		fr_array(arr);
		return (1);
	}
	free(trim);
	fr_array(arr);
	return (0);
}

int	store_elem(t_elements *elem, char *line)
{
	char	**arr;
	char	*trim;

	arr = NULL;
	trim = ft_strtrim(line, " \t\v\f\r\n");
	if (!trim)
		return (1);
	if (trim[0] == 'N' || trim[0] == 'S' || trim[0] == 'W' || trim[0] == 'E')
		return (handle_tex(elem, trim, arr));
	else if (trim[0] == 'F' && trim[1] == ' ')
		elem->floor = parse_rgb(trim + 1);
	else if (trim[0] == 'C' && trim[1] == ' ')
		elem->ceiling = parse_rgb(trim + 1);
	else
		return (free(trim), 1);
	if (elem->floor == -1 || elem->ceiling == -1)
		return (free(trim), 1);
	free(trim);
	return (0);
}
