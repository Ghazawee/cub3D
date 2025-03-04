/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2dmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:41 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:10:42 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_colour(t_textures *texture, int tex_x, int tex_y, t_ray *ray)
{
	t_image	*current_tex;
	int		offset;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			current_tex = &texture->ea;
		else
			current_tex = &texture->we;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			current_tex = &texture->so;
		else
			current_tex = &texture->no;
	}
	if (tex_x < 0 || tex_x >= current_tex->width || tex_y < 0
		|| tex_y >= current_tex->height)
		return (0x000000);
	offset = (tex_y * current_tex->line_len) + (tex_x * (current_tex->bpp / 8));
	return (*(int *)(current_tex->addr + offset));
}

void	colour_floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(&data->image, x, y, data->elements.ceiling);
			else
				my_mlx_pixel_put(&data->image, x, y, data->elements.floor);
			x++;
		}
		y++;
	}
}

void	put_pxl_wall(t_data *data, t_draw_walls *draw, t_ray *ray, int x)
{
	draw->drawstart = -draw->lineheight / 2 + WIN_HEIGHT / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + WIN_HEIGHT / 2;
	if (draw->drawend >= WIN_HEIGHT)
		draw->drawend = WIN_HEIGHT - 1;
	while (draw->drawstart < draw->drawend)
	{
		draw->step = 1.0 * draw->current_tex->height / draw->lineheight;
		draw->tex_pos = (draw->drawstart - (-draw->lineheight / 2 + WIN_HEIGHT
					/ 2)) * draw->step;
		draw->tex_y = (int)draw->tex_pos & (draw->current_tex->height - 1);
		draw->colour = get_pixel_colour(&data->texture, draw->tex_x,
				draw->tex_y, ray);
		if (ray->side == 1)
			draw->colour = (draw->colour & 0xfefefe) >> 1;
		my_mlx_pixel_put(&data->image, x, draw->drawstart, draw->colour);
		draw->drawstart++;
	}
}

void	draw_walls(t_ray *ray, t_data *data, int x)
{
	t_draw_walls	draw;

	draw.lineheight = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			draw.current_tex = &data->texture.ea;
		else
			draw.current_tex = &data->texture.we;
		draw.wall_x = data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			draw.current_tex = &data->texture.so;
		else
			draw.current_tex = &data->texture.no;
		draw.wall_x = data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	draw.wall_x -= floor(draw.wall_x);
	draw.tex_x = (int)(draw.wall_x * (double)draw.current_tex->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		draw.tex_x = draw.current_tex->width - draw.tex_x - 1;
	put_pxl_wall(data, &draw, ray, x);
}
