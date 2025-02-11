#include "../cub3d.h"

int exit_window(t_data *data)
{
    free_data(data);
    free(data->mlx.mlx);
    mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    free(data->mlx.win);
    exit(0);
}

void move_vertically(t_data *data, int direction)
{
    double new_x;
    double new_y;
    int curr_y;
    int curr_x;

    curr_y = (int)data->player.pos_y;
    curr_x = (int)data->player.pos_x;
    if(direction == MUP)
    {
        new_x = data->player.pos_x + data->player.dir_x * MOV_SPEED;
        if(data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y + data->player.dir_y * MOV_SPEED;
        if (data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
    else
    {
        new_x = data->player.pos_x - data->player.dir_x * MOV_SPEED;
         if(data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y - data->player.dir_y * MOV_SPEED;
        if (data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
}
// might need to change the way of checking  maybe check if new x first with current y and then check if new y with current x
void move_horizontally(t_data *data, int direction)
{
    double new_x;
    double new_y;
    int curr_y;
    int curr_x;

    curr_y = (int)data->player.pos_y;
    curr_x = (int)data->player.pos_x;
    if (direction == MRIGHT)
    {
        new_x = data->player.pos_x + data->player.plane_x * MOV_SPEED;
        if(data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y + data->player.plane_y * MOV_SPEED;
        if (data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
    else
    {
        new_x = data->player.pos_x - data->player.plane_x * MOV_SPEED;
        if(data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y - data->player.plane_y * MOV_SPEED;    
       if (data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
       
}
void rotate(t_player *pl, int direction)
{
    double rot;
    double old_dir_x;
    double old_plane_x;
    
    if(direction == R_ROTATE)
        rot = -ROT_SPEED;
    else
        rot = ROT_SPEED;

    old_dir_x = pl->dir_x;
    pl->dir_x = pl->dir_x * cos(rot) - pl->dir_y * sin(rot);
    pl->dir_y = old_dir_x * sin(rot) + pl->dir_y * cos(rot);
    old_plane_x = pl->plane_x;
    pl->plane_x = pl->plane_x * cos(rot) - pl->plane_y * sin(rot);
    pl->plane_y = old_plane_x * sin(rot) + pl->plane_y * cos(rot);
}

int key_events(int keycode, t_data *data)
{
    if (keycode == 65307)
        exit_window(data);
    if (keycode == 119)
        move_vertically(data, MUP); // can make it one function and send flag same for others
    if (keycode == 115)
        move_vertically(data, MDOWN);
    if (keycode == 97)
        move_horizontally(data, MLEFT);
    if (keycode == 100)
        move_horizontally(data, MRIGHT);
    if (keycode == 65361)
        rotate(&data->player, L_ROTATE);
    if (keycode == 65363)
        rotate(&data->player, R_ROTATE);
    return(0);
}
