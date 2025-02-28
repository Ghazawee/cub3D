#include "../cub3d.h"

void colour_floor_ceil(t_data *data)
{
    int y;
    int x;

    y = 0;
    while(y < WIN_HEIGHT/2)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            my_mlx_pixel_put(&data->image, x, y, data->elements.ceiling);
            x++;
        }
        y++;
    }
    while(y < WIN_HEIGHT -1)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
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

    //ray has variable called lineheight now
    //for the drawstart and drawend there is a struct t_draw, that contains i think everything for drawing
    lineheight = (int)(WIN_HEIGHT / ray->perp_wall_dist); // height of line 1/perp_wall_dist * win_height to pixel the coordinate
    drawstart = -lineheight / 2 + WIN_HEIGHT / 2; // win height/2 is the center of the screen, -lineheight/2, since lineheight goes above and below the center of screen
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
