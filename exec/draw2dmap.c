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

int get_pixel_colour(t_textures *texture, int tex_x, int tex_y, t_ray *ray)
{
    t_image *current_tex;
    
    // Select texture based on wall direction
    if (ray->side == 0) {
        if (ray->ray_dir_x > 0)
            current_tex = &texture->we;
        else
            current_tex = &texture->ea;
    } else {
        if (ray->ray_dir_y > 0)
            current_tex = &texture->so;
        else
            current_tex = &texture->no;
    }
    
    // Bounds checking
    if (tex_x < 0 || tex_x >= current_tex->width || tex_y < 0 || tex_y >= current_tex->height)
        return (0x000000);
        
    int offset = (tex_y * current_tex->line_len) + (tex_x * (current_tex->bpp / 8));
    return (*(int*)(current_tex->addr + offset));
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
void draw_walls(t_ray *ray, t_data *data, int x)
{
    int lineheight;
    int drawstart;
    int drawend;
    int colour;
    double wall_x; // Where exactly the wall was hit
    int tex_x, tex_y;
    t_image *current_tex;

    // Calculate height of line to draw
    lineheight = (int)(WIN_HEIGHT / ray->perp_wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
    if(drawstart < 0)
        drawstart = 0;
    drawend = lineheight / 2 + WIN_HEIGHT / 2;
    if(drawend >= WIN_HEIGHT)
        drawend = WIN_HEIGHT - 1;
    
    // Select texture based on wall direction
    if (ray->side == 0) {
        if (ray->ray_dir_x > 0)
            current_tex = &data->texture.we;  // West texture
        else
            current_tex = &data->texture.ea;  // East texture
        wall_x = data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    } else {
        if (ray->ray_dir_y > 0)
            current_tex = &data->texture.so;  // South texture
        else
            current_tex = &data->texture.no;  // North texture
        wall_x = data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    }
    
    // Get the fractional part of wall_x
    wall_x -= floor(wall_x);
    
    // Calculate the texture x-coordinate
    tex_x = (int)(wall_x * (double)current_tex->width);
    // Flip texture x-coordinate if needed
    if ((ray->side == 0 && ray->ray_dir_x < 0) || 
        (ray->side == 1 && ray->ray_dir_y > 0))
        tex_x = current_tex->width - tex_x - 1;
    
    // Drawing the texture stripe
    int y = drawstart;
    while (y < drawend)
    {
        // Calculate texture y-coordinate
        double step = 1.0 * current_tex->height / lineheight;
        double tex_pos = (y - (-lineheight / 2 + WIN_HEIGHT / 2)) * step;
        tex_y = (int)tex_pos & (current_tex->height - 1);
        
        // Get pixel color from texture
        colour = get_pixel_colour(&data->texture, tex_x, tex_y, ray);
        
        // Make color darker for y-sides
        if (ray->side == 1)
            colour = (colour & 0xfefefe) >> 1;
            
        my_mlx_pixel_put(&data->image, x, y, colour);
        y++;
    }
}
