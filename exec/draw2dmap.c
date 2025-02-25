#include "../cub3d.h"

// int  get_pixel_colour(t_data *data, int x, int drawstart)
// {
//     int height;
//     int width;
//     void *texture;
//     char *addr;
//     texture = mlx_xpm_file_to_image(data->mlx.mlx, data->elements.no, &width, &height);
//     addr = mlx_get_data_addr(texture, &data->image.bpp, &data->image.line_len, &data->image.endian);
//     printf("pixel colour  ----  %d\n", *(int *)(addr + (drawstart * data->image.line_len) + (x * (data->image.bpp / 8))));
//     // *(int *)(tex_data + (y * size_line) + (x * (bpp / 8)));
//     return (*(int *)(addr + (drawstart * data->image.line_len) + (x * (data->image.bpp / 8))));
// }

int get_pixel_colour(t_textures *texture, int x, int y, t_ray *ray)
{

    // if (x < 0 || x >= texture->no.width || y < 0 || y >= texture->no.height)
    //     return (0x000000); // Return black if out of bounds
    if ((ray->side == 1 && ray->ray_dir_y < 0))
    {
        int offset = (y * texture->no.line_len) + (x * (texture->no.bpp / 8));
        return (*(int *)(texture->no.addr + offset));
    }
    return (0x000000);
}

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
        colour = get_pixel_colour(&data->texture, x, drawstart, ray);
    else
        colour = get_pixel_colour(&data->texture, x, drawstart, ray);
    if ((ray->side == 1 && ray->ray_dir_y < 0) || (ray->side == 0 && ray->ray_dir_x > 0))
        colour = (colour & 0xfefefe) >> 1;
    while(drawstart < drawend)
    {
        my_mlx_pixel_put(&data->image, x, drawstart, colour);
        drawstart++;
    }
}
