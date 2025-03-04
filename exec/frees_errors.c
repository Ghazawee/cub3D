/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:44 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:13:33 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fr_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_data(t_data *data)
{
	free(data->map.fullcub);
	if (data->map.cmap)
		fr_array(data->map.cmap);
	if (data->map.map)
		fr_array(data->map.map);
	free(data->elements.no);
	free(data->elements.so);
	free(data->elements.we);
	free(data->elements.ea);
}

int	file_error(int id)
{
	if (id == 0)
		return (err_msg("Error: File Empty\n"));
	else if (id == -2)
	{
		perror("Error");
		return (0);
	}
	else if (id == -1)
		return (err_msg("Error: File too large\n"));
	return (0);
}

void	destroy_imgs(t_data *data)
{
	if (data->texture.no.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.no.img);
	if (data->texture.so.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.so.img);
	if (data->texture.we.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.we.img);
	if (data->texture.ea.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.ea.img);
}
