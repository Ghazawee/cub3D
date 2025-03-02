#include "../cub3d.h"

int exit_window(t_data *data)
{
    destroy_imgs(data);
    if(data->image.img)
        mlx_destroy_image(data->mlx.mlx, data->image.img);
    if(data->mlx.win)
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    if(data->mlx.mlx)
    {
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
    }
    free_data(data);
    exit(0);
}


// void move_player(t_data *data, double move_x, double move_y, t_cord vars)
// {
//     int wall_ahead;
//     int wall_x;
//     int wall_y;
//     double buffer = 0.5;
//     static double prev_x = -1;
//     static double prev_y = -1;
    
//     // Initialize on first run
//     if (prev_x == -1) {
//         prev_x = data->player.pos_x;
//         prev_y = data->player.pos_y;
//     }

//     double new_x = data->player.pos_x + move_x;
//     double new_y = data->player.pos_y + move_y;

//     vars.new_x = (int)(data->player.pos_x + move_x);
//     vars.new_y = (int)(data->player.pos_y + move_y);
//     vars.curr_x = (int)data->player.pos_x;
//     vars.curr_y = (int)data->player.pos_y;
//     if (vars.new_y < 0 || vars.new_y >= data->map.rows || 
//         vars.curr_y < 0 || vars.curr_y >= data->map.rows) {
//         return;  // Invalid position, don't move
//     }
//     // if (new_y < buffer || new_y >= data->map.rows - buffer || 
//     //     new_x < buffer) {
//     //     printf("too close to edge");return;  // Too close to edge, don't move
//     // }
//     vars.row_length_y = (int)ft_strlen(data->map.map[vars.new_y]);
//     vars.row_length_cy = (int)ft_strlen(data->map.map[vars.curr_y]);
//     if (vars.new_x < 0 || vars.new_x >= vars.row_length_y || 
//         vars.curr_x < 0 || vars.curr_x >= vars.row_length_cy) {
//         printf("Outside row bounds\n");
//         return;
//     }
//     if (new_y < buffer || new_y >= data->map.rows - buffer || 
//         new_x < buffer || new_x >= vars.row_length_y - buffer) {
//         printf("Too close to edge\n");
//         return;
//     }
//     if (data->map.map[vars.new_y][vars.new_x] == ' ' || 
//         data->map.map[vars.curr_y][vars.new_x] == ' ' || 
//         data->map.map[vars.new_y][vars.curr_x] == ' ') {
//         printf("Cannot move through spaces\n");
//         return;
//     }
//     wall_ahead = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.new_x] == '1');
//     wall_x = (vars.curr_y >= 0 && vars.curr_y < data->map.rows && 
//         vars.new_x >= 0 && vars.new_x < vars.row_length_cy &&
//         data->map.map[vars.curr_y][vars.new_x] == '1');
//     wall_y = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
//         vars.curr_x >= 0 && vars.curr_x < vars.row_length_y &&
//         data->map.map[vars.new_y][vars.curr_x] == '1');
//     if (wall_ahead && (!wall_x && !wall_y))
//         return;
//     if (!wall_x)
//         data->player.pos_x += move_x;
//     if (!wall_y)
//         data->player.pos_y += move_y;

//     double dx = data->player.pos_x - prev_x;
//     double dy = data->player.pos_y - prev_y;
//     double distance = sqrt(dx*dx + dy*dy);
    
//     if (distance > 0.2) {
//         printf("Jump detected: %f,%f to %f,%f (distance: %f)\n", 
//                 prev_x, prev_y, data->player.pos_x, data->player.pos_y, distance);
//         data->player.pos_x = prev_x;
//         data->player.pos_y = prev_y;
//     } else {
//         prev_x = data->player.pos_x;
//         prev_y = data->player.pos_y;
//     }
//     printf("Player position: %f, %f\n", data->player.pos_x, data->player.pos_y);
// }

void move_vertically(t_data *data, int direction)
{
    t_cord vars;
    double move_x;
    double move_y;

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

void move_horizontally(t_data *data, int direction)
{
    t_cord vars;
    double move_x;
    double move_y;

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

void rotate(t_player *pl, int direction, t_data *data)
{
    double rot;
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;
    
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

int key_events(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
        exit_window(data);
    if (keycode == W_KEY)
        move_vertically(data, MUP); // can make it one function and send flag same for others
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
    return(0);
}
