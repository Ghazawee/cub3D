#include "../cub3d.h"

void colour_floor_ceiling(t_data *data)
{
    int x;
    int y;

    y = 0;
    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            if(y < WIN_HEIGHT / 2)
                my_mlx_pixel_put(&data->image, x, y, data->elements.ceiling);
            else
                my_mlx_pixel_put(&data->image, x, y, data->elements.floor);
            x++;
        }
        y++;
    }
}
//i think for textures we use similar approach to draw them
void    draw_walls(t_ray *ray, t_data *data, int x)
{
    int lineheight;
    int drawstart;
    int drawend;
    int colour;

    lineheight = (int)(WIN_HEIGHT / ray->perp_wall_dist);
    drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
    if(drawstart < 0)
        drawstart = 0;
    drawend = lineheight / 2 + WIN_HEIGHT / 2;
    if(drawend >= WIN_HEIGHT)
        drawend = WIN_HEIGHT - 1;
    if (data->map.map[ray->map_y][ray->map_x] == '1')
        colour = 0x00FF00;
    else
        colour = 0xFF0000;
    if (ray->side == 1)
        colour = (colour & 0xfefefe) >> 1;
    while(drawstart < drawend)
    {
        my_mlx_pixel_put(&data->image, x, drawstart, colour);
        drawstart++;
    }
}
