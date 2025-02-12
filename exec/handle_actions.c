#include "../cub3d.h"

int exit_window(t_data *data)
{
    if(data->image.img)
        mlx_destroy_image(data->mlx.mlx, data->image.img);
    if(data->mlx.win)
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    if(data->mlx.mlx)
        free(data->mlx.mlx);
    free_data(data);
    // mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    // free(data->mlx.mlx);
    // free(data->mlx.mlx);
    exit(0);
}

void move_vertically(t_data *data, int direction)
{
    double new_x;
    double new_y;
    // int next_x;
    // int next_y;
    int curr_y;
    int curr_x;
    // double move;
    curr_y = (int)data->player.pos_y;
    curr_x = (int)data->player.pos_x;
    // if(direction == MUP)
    //     move = MOV_SPEED * 1;
    // else
    //     move = MOV_SPEED * -1;
    // new_x = data->player.pos_x + data->player.dir_x * move;
    // new_y = data->player.pos_y + data->player.dir_y * move;

    // next_x = (int)new_x;
    // next_y = (int)new_y;
    // if (next_y >= 0 && next_y < data->map.rows &&
    //     next_x >= 0 && next_x < (int)ft_strlen(data->map.map[next_y]) &&
    //     data->map.map[next_y][next_x] != '1')
    // {
    //     data->player.pos_x = new_x;
    //     data->player.pos_y = new_y;
    // }
    if(direction == MUP)
    {
        new_x = data->player.pos_x + data->player.dir_x * MOV_SPEED;
        if(curr_y >= 0 && curr_y < data->map.rows && (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) && 
            data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y + data->player.dir_y * MOV_SPEED;
        if ((int)new_y >= 0 && (int)new_y < data->map.rows && curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) 
            && data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
    else
    {
        new_x = data->player.pos_x - data->player.dir_x * MOV_SPEED;
        if(curr_y >= 0 && curr_y < data->map.rows && (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) && 
            data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y - data->player.dir_y * MOV_SPEED;
        if ((int)new_y >= 0 && (int)new_y < data->map.rows && curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) 
            && data->map.map[(int)new_y][curr_x] != '1')
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
    // int next_y;
    // int next_x;
    // double move;

    // if(direction == MLEFT)
    //     move = MOV_SPEED * -1;
    // else
    //     move = MOV_SPEED * 1;
    curr_y = (int)data->player.pos_y;
    curr_x = (int)data->player.pos_x;
    // new_x = data->player.pos_x + data->player.plane_x * move;
    // new_y = data->player.pos_y + data->player.plane_y * move;
    // next_x = (int)new_x;
    // next_y = (int)new_y;
    // if (next_y >= 0 && next_y < data->map.rows &&
    //     next_x >= 0 && next_x < (int)ft_strlen(data->map.map[next_y]) &&
    //     data->map.map[next_y][next_x] != '1')
    // {
    //     data->player.pos_x = new_x;
    //     data->player.pos_y = new_y;
    // }
    if (direction == MRIGHT)
    {
        new_x = data->player.pos_x + data->player.plane_x * MOV_SPEED;
        // if(data->map.map[curr_y][(int)new_x] != '1')
        if (curr_y >= 0 && curr_y < data->map.rows &&
            (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) &&
            data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y + data->player.plane_y * MOV_SPEED;
        // if (data->map.map[(int)new_y][curr_x] != '1')
        if ((int)new_y >= 0 && (int)new_y < data->map.rows &&
        curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) &&
        data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }
    else
    {
        new_x = data->player.pos_x - data->player.plane_x * MOV_SPEED;
        // if(data->map.map[curr_y][(int)new_x] != '1')
        if (curr_y >= 0 && curr_y < data->map.rows &&
            (int)new_x >= 0 && (int)new_x < (int)ft_strlen(data->map.map[curr_y]) &&
            data->map.map[curr_y][(int)new_x] != '1')
            data->player.pos_x = new_x;
        new_y = data->player.pos_y - data->player.plane_y * MOV_SPEED;    
    //    if (data->map.map[(int)new_y][curr_x] != '1')
        if ((int)new_y >= 0 && (int)new_y < data->map.rows &&
        curr_x >= 0 && curr_x < (int)ft_strlen(data->map.map[(int)new_y]) &&
        data->map.map[(int)new_y][curr_x] != '1')
            data->player.pos_y = new_y;
    }  
}
void rotate(t_player *pl, int direction)
{
    double rot;
    double old_dir_x;
    double old_plane_x;
    double cos_rot;
    double sin_rot;
    
    if(direction == R_ROTATE)
        rot = ROT_SPEED;
    else
        rot = -ROT_SPEED;
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
        rotate(&data->player, L_ROTATE);
    if (keycode == RIGHT_ARROW)
        rotate(&data->player, R_ROTATE);
    return(0);
}
