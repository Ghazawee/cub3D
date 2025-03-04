/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:11:03 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:11:04 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Digital differntial analysis algorithm
void	dda_algo(t_ray *ray, t_data *data)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map.rows
			|| ray->map_x >= (int)ft_strlen(data->map.map[ray->map_y]))
		{
			ray->hit = 1;
			break ;
		}
		if (data->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	init_step_side(t_ray *ray, t_player *player, t_data *data)
{
	(void)data;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

int	render_frames(t_data *data)
{
	struct timeval	current;

	ft_bzero(data->image.addr, WIN_WIDTH * WIN_HEIGHT * (data->image.bpp / 8));
	gettimeofday(&current, NULL);
	data->delta_time = (current.tv_sec - data->last.tv_sec) + (current.tv_usec
			- data->last.tv_usec) * 1e-6;
	if (data->delta_time > 0.1)
		data->delta_time = 0.1;
	data->last = current;
	check_movement(data);
	colour_floor_ceiling(data);
	cast_rays(&data->ray, &data->player, data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.img, 0,
		0);
	return (0);
}
