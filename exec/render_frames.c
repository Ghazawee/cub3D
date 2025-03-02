#include "../cub3d.h"

//Digital differntial analysis algorithm
void dda_algo(t_ray *ray, t_data *data)
{
    ray->hit = 0;
    while(!ray->hit)
    {
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
        if(ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= data->map.rows 
            || ray->map_x >= (int)ft_strlen(data->map.map[ray->map_y]))
        {
            ray->hit = 1;
            ray->side = 2; // Special value for out-of-bounds
            break;
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


void init_ray_delta(t_ray *ray, t_player *player, int x)
{
    ray->camera_x = (2 * x / (double)WIN_WIDTH) - 1; //spreads rays evenly in our fov from left to right/ -1 to 1 
    ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // distance to next x grid line, 1 / ray_dir_x because we're just moving one block at a time
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
}


void cast_rays(t_ray *ray, t_player *player, t_data *data)
{
    int x;

    x = 0;
    while(x < WIN_WIDTH) // might change to < 30 or something smaller for performance, the more rays the higher resolution but at cost of performance// for visualizing i think low res is fine because its a 2d map
    {
        init_ray_delta(ray, player, x);
        init_step_side(ray, player, data);
        dda_algo(ray, data);
        if(ray->side == 0)
            ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
        else
            ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
        ray->line_height = (int) (WIN_HEIGHT/ ray->perp_wall_dist);
        ray->wallx = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y; // exact pos of where line hit in the wall//idk if it should be posy ray_dir_y when side==0, but thats what the document says
        if(ray->side == 1)
            ray->wallx = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
        ray->wallx -= floor(ray->wallx);
        draw_walls(ray, data, x);
        x++;
    }
}

int    render_frames(t_data *data)
{
    struct timeval current;

    ft_bzero(data->image.addr, WIN_WIDTH * WIN_HEIGHT * (data->image.bpp / 8));
    gettimeofday(&current, NULL);
    data->delta_time = (current.tv_sec - data->last.tv_sec) + (current.tv_usec - data->last.tv_usec)* 1e-6;
    if(data->delta_time > 0.1)
        data->delta_time = 0.1;
    data->last = current;
    if(data->keys[0])
        move_vertically(data, MUP);
    if(data->keys[1])
        move_vertically(data, MDOWN);
    if(data->keys[2])
        move_horizontally(data, MLEFT);
    if(data->keys[3])
        move_horizontally(data, MRIGHT);
    if(data->keys[4])
        rotate(&data->player, L_ROTATE, data);
    if(data->keys[5])
        rotate(&data->player, R_ROTATE, data);
    colour_floor_ceiling(data);
    cast_rays(&data->ray, &data->player, data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.img, 0, 0);
    return(0);
}
