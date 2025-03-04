/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:38 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:10:39 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_start_game(t_data *data)
{
	gettimeofday(&data->last, NULL);
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		write(2, "Error: mlx_init failed\n", 24);
		free_data(data);
		exit(1);
	}
	init_texture(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!data->mlx.win)
	{
		write(2, "Error: mlx_new_window failed\n", 29);
		destroy_imgs(data);
		free(data->mlx.mlx);
		free_data(data);
		exit(1);
	}
	data->image.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_len, &data->image.endian);
	init_player(data);
	mlx_loops_hooks(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error: Invalid file extension\n", 30);
		return (1);
	}
	printf("file: %s valid\n", av[1]);
	init_data(&data);
	if (!parse_elem_map(av[1], &data))
	{
		free_data(&data);
		return (1);
	}
	init_start_game(&data);
	free_data(&data);
}
