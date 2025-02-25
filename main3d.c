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
	ft_bzero(&data->texture, sizeof(t_textures));
	// ft_bzero(&data->texture.no, sizeof(t_image));
	// ft_bzero(&data->texture.so, sizeof(t_image));
	// ft_bzero(&data->texture.we, sizeof(t_image));
	// ft_bzero(&data->texture.ea, sizeof(t_image));
	ft_bzero(data->keys, 7);
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
		data->player.dir_y = -1; // -0.1 to make it like superliminal
		data->player.plane_x = 0.66; // FOV at 66 degrees, 2 * arctan(0.66/1.0) = 66 degrees
	}
	else if (data->map.direction == 'S')
	{
		data->player.dir_y = 1; // 0.1 to make it like superliminal
		data->player.plane_x = -0.66;
	}
	else if (data->map.direction == 'W')
	{
		data->player.dir_x = -1; // -0.1 to make it like superliminal
		data->player.plane_y = -0.66;
	}
	else if (data->map.direction == 'E')
	{
		data->player.dir_x = 1; // 0.1 to make it like superliminal
		data->player.plane_y = 0.66;
	}
}

int key_press(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys[0] = 1;
	if (keycode == S_KEY)
		data->keys[1] = 1;
	if (keycode == A_KEY)
		data->keys[2] = 1;
	if (keycode == D_KEY)
		data->keys[3] = 1;
	if (keycode == LEFT_ARROW)
		data->keys[4] = 1;
	if (keycode == RIGHT_ARROW)
		data->keys[5] = 1;
	if (keycode == ESC_KEY)
		exit_window(data);
	return (0);
}
int key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys[0] = 0;
	if (keycode == S_KEY)
		data->keys[1] = 0;
	if (keycode == A_KEY)
		data->keys[2] = 0;
	if (keycode == D_KEY)
		data->keys[3] = 0;
	if (keycode == LEFT_ARROW)
		data->keys[4] = 0;
	if (keycode == RIGHT_ARROW)
		data->keys[5] = 0;
	return (0);
}

void init_texture(t_data *data)
{
	printf("%s\n", data->elements.no);
	data->texture.no.img = mlx_xpm_file_to_image(data->mlx.mlx, data->elements.no, &data->texture.no.width, &data->texture.no.height);
	// abort();
	if (data->texture.no.img == NULL)
	{
		write(2, "Error: mlx_xpm_file_to_image failed\n", 36);
		// free_data(data);
		exit(1);
	}
	data->texture.no.addr = mlx_get_data_addr(data->texture.no.img, &data->texture.no.bpp, &data->texture.no.line_len, &data->texture.no.endian);
	data->texture.so.img = mlx_xpm_file_to_image(data->mlx.mlx, data->elements.so, &data->texture.so.width, &data->texture.so.height);
	data->texture.so.addr = mlx_get_data_addr(data->texture.so.img, &data->texture.so.bpp, &data->texture.so.line_len, &data->texture.so.endian);
	data->texture.we.img = mlx_xpm_file_to_image(data->mlx.mlx, data->elements.we, &data->texture.we.width, &data->texture.we.height);
	data->texture.we.addr = mlx_get_data_addr(data->texture.we.img, &data->texture.we.bpp, &data->texture.we.line_len, &data->texture.we.endian);
	data->texture.ea.img = mlx_xpm_file_to_image(data->mlx.mlx, data->elements.ea, &data->texture.ea.width, &data->texture.ea.height);
	data->texture.ea.addr = mlx_get_data_addr(data->texture.ea.img, &data->texture.ea.bpp, &data->texture.ea.line_len, &data->texture.ea.endian);
}

void	init_start_game(t_data *data)
{
	gettimeofday(&data->last, NULL);
	data->mlx.mlx = mlx_init();
	init_texture(data);
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
	printf("player spawn pos X and Y - %f, %f\n", data->player.pos_x, data->player.pos_y);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	// mlx_hook(data->mlx.win, 2, 1L << 0, key_events, data);
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
