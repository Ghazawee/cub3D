#include "../cub3d.h"

//Digital differntial analysis algorithm
void dda_algo(t_ray *ray, t_data *data)
{
    ray->hit = 0;
    while(!ray->hit)
    {
        if(ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map.rows 
            || ray->map_x >= (int)ft_strlen(data->map.map[ray->map_y]))
        {
            ray->hit = 1;
            break;
        }
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
        if (data->map.map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void init_step_side(t_ray *ray, t_player *player, t_data *data)
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
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
}



void cast_rays(t_ray *ray, t_player *player, t_data *data)
{
    int i;
    // int j;

    i = 0;
    while(i < WIN_WIDTH) // might change to < 30 or something smaller for performance, the more rays the higher resolution but at cost of performance// for visualizing i think low res is fine because its a 2d map
    {
        ray->camera_x = (2 * i / (double)WIN_WIDTH) - 1; //spreads rays evenly in our fov from left to right/ -1 to 1 
        ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
        ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
        ray->map_x = (int)player->pos_x;
        ray->map_y = (int)player->pos_y;
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // distance to next x grid line, 1 / ray_dir_x because we're just moving one block at a time
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
        ray->hit = 0;
        init_step_side(ray, player, data);
        dda_algo(ray, data);
        if(ray->side == 0)
            ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
        else
            ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
        draw_walls(ray, data, i);
        //need to implement function to draw rayys as lines to visualize// later on start calculating distance to wall and stuff i think instead of drawing a line
        i++;
    }
}

int    render_frames(t_data *data)
{
    t_vars vars;

    // mlx_clear_window(data->mlx.mlx, data->mlx.win);
    ft_bzero(data->image.addr, WIN_WIDTH * WIN_HEIGHT * (data->image.bpp / 8));
    init_vars(&vars);
    // draw_gmap(&data->map, &vars, data);
    // init_vars(&vars);
    // draw_player(&data->player, &vars, data);
    // draw_grid_map(data);// need to implement to visualize,
    cast_rays(&data->ray, &data->player, data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.img, 0, 0);
    return(0);
}