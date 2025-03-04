/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:51 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:10:52 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_data *data)
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

int	key_release(int keycode, t_data *data)
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

int	key_events(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		exit_window(data);
	if (keycode == W_KEY)
		move_vertically(data, MUP);
	if (keycode == S_KEY)
		move_vertically(data, MDOWN);
	if (keycode == A_KEY)
		move_horizontally(data, MLEFT);
	if (keycode == D_KEY)
		move_horizontally(data, MRIGHT);
	if (keycode == LEFT_ARROW)
		rotate(&data->player, L_ROTATE, data);
	if (keycode == RIGHT_ARROW)
		rotate(&data->player, R_ROTATE, data);
	return (0);
}

void	check_movement(t_data *data)
{
	if (data->keys[0])
		move_vertically(data, MUP);
	if (data->keys[1])
		move_vertically(data, MDOWN);
	if (data->keys[2])
		move_horizontally(data, MLEFT);
	if (data->keys[3])
		move_horizontally(data, MRIGHT);
	if (data->keys[4])
		rotate(&data->player, L_ROTATE, data);
	if (data->keys[5])
		rotate(&data->player, R_ROTATE, data);
}
