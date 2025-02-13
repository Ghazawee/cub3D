#include "../cub3d.h"

//remove this and player drawing useless and might mess later no minimap feature
void draw_gmap(t_map *map, t_vars *v, t_data *data)
{
    int tile_size;
    int colour;
    t_image *img;

    tile_size = 20;
    img = &data->image;
    while(v->i < map->rows)
    {
        v->j = 0;
        while(v->j < (int)ft_strlen(map->map[v->i]))
        {
            if(map->map[v->i][v->j] == '1' || map->map[v->i][v->j] == ' ')
                colour = 0xFFFFFF;
            else
                colour = 0x000000;
            v->k = 0;
            while(v->k < tile_size)
            {
                v->c = 0;
                while (v->c < tile_size)
                {
                    if(v->k == 0 || v->c == 0)
                        my_mlx_pixel_put(img, v->j * tile_size + v->c, v->i * tile_size + v->k, 0x808080);
                    else
                        my_mlx_pixel_put(img, v->j * tile_size + v->c, v->i * tile_size + v->k, colour);
                    v->c++;
                }
                v->k++;
            }
            v->j++;
        }
        v->i++;
    }
}

void draw_player(t_player *player, t_vars *v, t_data *data)
{
    int tile_size;
    t_image *img;
    int screen_x;
    int screen_y;
    int px;
    int py;

    init_vars(v);
    tile_size = 20;
    img = &data->image;

    screen_y = (int)(player->pos_y * tile_size);
    screen_x = (int)(player->pos_x * tile_size);
    v->k = -3;
    while(v->k <= 3)
    {
        v->c = -3;
        while(v->c <= 3)
        {
            px = screen_x + v->c;
            py = screen_y + v->k;
            if(px >= 0 && px < WIN_WIDTH && py >= 0 && py < WIN_HEIGHT)
                my_mlx_pixel_put(img, px, py, 0xFF0000);
            // my_mlx_pixel_put(img, v->j + v->c, v->i + v->k, 0xFF0000);
            v->c++;
        }
        v->k++;
    }
}
//i think for textures we use similar approach to draw them
void    draw_walls(t_ray *ray, t_data *data, int i)
{
    int lineheight;
    int drawstart;
    int drawend;
    int colour;

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
        my_mlx_pixel_put(&data->image, i, drawstart, colour);
        drawstart++;
    }
}
