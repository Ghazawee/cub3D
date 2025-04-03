/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:48 by hbasheer          #+#    #+#             */
/*   Updated: 2025/04/03 17:08:13 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_window(t_data *data)
{
	destroy_imgs(data);
	if (data->image.img)
		mlx_destroy_image(data->mlx.mlx, data->image.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free(data->mlx.mlx);
	free_data(data);
	exit(0);
}

void	move_vertically(t_data *data, int direction)
{
	t_cord	vars;
	double	move_x;
	double	move_y;

	ft_bzero(&vars, sizeof(t_cord));
	if (direction == MUP)
	{
		move_x = data->player.dir_x * (MOV_SPEED * data->delta_time);
		move_y = data->player.dir_y * (MOV_SPEED * data->delta_time);
	}
	else
	{
		move_x = -data->player.dir_x * (MOV_SPEED * data->delta_time);
		move_y = -data->player.dir_y * (MOV_SPEED * data->delta_time);
	}
	move_player(data, move_x, move_y, vars);
}

void	move_horizontally(t_data *data, int direction)
{
	t_cord	vars;
	double	move_x;
	double	move_y;

	ft_bzero(&vars, sizeof(t_cord));
	if (direction == MRIGHT)
	{
		move_x = data->player.plane_x * (MOV_SPEED * data->delta_time);
		move_y = data->player.plane_y * (MOV_SPEED * data->delta_time);
	}
	else
	{
		move_x = -data->player.plane_x * (MOV_SPEED * data->delta_time);
		move_y = -data->player.plane_y * (MOV_SPEED * data->delta_time);
	}
	move_player(data, move_x, move_y, vars);
}

void	rotate(t_player *pl, int direction, t_data *data)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	if (direction == R_ROTATE)
		rot = ROT_SPEED * data->delta_time;
	else
		rot = -ROT_SPEED * data->delta_time;
	if (fabs(rot) > 0.1)
	{
		if (rot > 0)
			rot = 0.1;
		else
			rot = -0.1;
	}
	cos_rot = cos(rot);
	sin_rot = sin(rot);
	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos_rot - pl->dir_y * sin_rot;
	pl->dir_y = old_dir_x * sin_rot + pl->dir_y * cos_rot;
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos_rot - pl->plane_y * sin_rot;
	pl->plane_y = old_plane_x * sin_rot + pl->plane_y * cos_rot;
}
