/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:59 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:11:23 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray_delta(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = (2 * x / (double)WIN_WIDTH) - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	check_ray_side(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->side == 0)
	{
		ray->wallx = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
		if (ray->step_x < 0)
			ray->wallx = 1.0 - ray->wallx + floor(ray->wallx);
	}
	else
	{
		ray->wallx = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->step_y < 0)
			ray->wallx = 1.0 - ray->wallx + floor(ray->wallx);
	}
	ray->wallx -= floor(ray->wallx);
}

void	cast_rays(t_ray *ray, t_player *player, t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_delta(ray, player, x);
		init_step_side(ray, player, data);
		dda_algo(ray, data);
		check_ray_side(ray, player);
		draw_walls(ray, data, x);
		x++;
	}
}
