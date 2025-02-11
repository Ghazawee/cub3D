#include "cub3d.h"

// void	fr_arrray(char ***arr)
// {
//     int i;

// 	i = 0;
//     if (arr && *arr)
//     {
//         while ((*arr)[i])
//         {
//             free((*arr)[i]);
//             (*arr)[i] = NULL;
//             i++;
//         }
//         free(*arr);
//         *arr = NULL;
//     }
// }

void	fr_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i]=NULL;
		i++;
	}
	free(array);
	array = NULL;
}
void free_data(t_data *data)
{
	free(data->map.fullcub);
	if(data->map.cmap)
		fr_array(data->map.cmap);
	if(data->map.map)	
		fr_array(data->map.map);
	free(data->elements.no);
	free(data->elements.so);
	free(data->elements.we);
	free(data->elements.ea);
}

void	init_data(t_data *data)
{
	ft_bzero(&data->elements, sizeof(t_elements));
	ft_bzero(&data->map, sizeof(t_map));
	ft_bzero(&data->mlx, sizeof(t_mlx));
	ft_bzero(&data->player, sizeof(t_player));
	ft_bzero(&data->ray, sizeof(t_ray));
	ft_bzero(&data->image, sizeof(t_image));
}
void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_player(t_data *data)
{
	data->player.pos_x = data->map.p_x + 0.5;
	data->player.pos_y = data->map.p_y + 0.5;
	if (data->map.direction == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66; // FOV at 66 degrees, 2 * arctan(0.66/1.0) = 66 degrees
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

void	init_start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		write(2, "Error: mlx_init failed\n", 24);
		free_data(data);
		exit(1);
	}
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->mlx.win)
	{
		write(2, "Error: mlx_new_window failed\n", 29);
		free_data(data);
		exit(1);
	}
	data->image.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp, &data->image.line_len, &data->image.endian);
	init_player(data);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_events, data);
	mlx_hook(data->mlx.win, 17, 0, exit_window, data);
	// mlx_loop(data->mlx.mlx);
	mlx_loop_hook(data->mlx.mlx, render_frames, data);
	mlx_loop(data->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1); 
	}
	if(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
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
