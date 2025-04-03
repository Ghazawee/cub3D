/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:53 by hbasheer          #+#    #+#             */
/*   Updated: 2025/04/03 17:09:29 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(&data->elements, sizeof(t_elements));
	ft_bzero(&data->map, sizeof(t_map));
	ft_bzero(&data->mlx, sizeof(t_mlx));
	ft_bzero(&data->player, sizeof(t_player));
	ft_bzero(&data->ray, sizeof(t_ray));
	ft_bzero(&data->image, sizeof(t_image));
	ft_bzero(&data->texture, sizeof(t_textures));
	ft_bzero(data->keys, 7);
}

void	init_player(t_data *data)
{
	data->player.pos_x = data->map.p_x + 0.5;
	data->player.pos_y = data->map.p_y + 0.5;
	if (data->map.direction == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else if (data->map.direction == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	else if (data->map.direction == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
	else if (data->map.direction == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
}

void	xpm_to_image(t_data *data)
{
	data->texture.no.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.no, &data->texture.no.width,
			&data->texture.no.height);
	data->texture.so.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.so, &data->texture.so.width,
			&data->texture.so.height);
	data->texture.we.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.we, &data->texture.we.width,
			&data->texture.we.height);
	data->texture.ea.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.ea, &data->texture.ea.width,
			&data->texture.ea.height);
	if (data->texture.no.img == NULL || data->texture.so.img == NULL
		|| data->texture.we.img == NULL || data->texture.ea.img == NULL)
	{
		write(2, "Error: mlx_xpm_file_to_image failed\n", 36);
		destroy_imgs(data);
		free(data->mlx.mlx);
		free_data(data);
		exit(1);
	}
}

void	init_texture(t_data *data)
{
	xpm_to_image(data);
	data->texture.no.addr = mlx_get_data_addr(data->texture.no.img,
			&data->texture.no.bpp, &data->texture.no.line_len,
			&data->texture.no.endian);
	data->texture.so.addr = mlx_get_data_addr(data->texture.so.img,
			&data->texture.so.bpp, &data->texture.so.line_len,
			&data->texture.so.endian);
	data->texture.we.addr = mlx_get_data_addr(data->texture.we.img,
			&data->texture.we.bpp, &data->texture.we.line_len,
			&data->texture.we.endian);
	data->texture.ea.addr = mlx_get_data_addr(data->texture.ea.img,
			&data->texture.ea.bpp, &data->texture.ea.line_len,
			&data->texture.ea.endian);
}

void	mlx_loops_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 17, 0, exit_window, data);
	mlx_loop_hook(data->mlx.mlx, render_frames, data);
	mlx_loop(data->mlx.mlx);
}
