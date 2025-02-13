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
//ithink not needed anymore
void diagonal_blocked(t_data *data, double move_x,double move_y, t_cord *vars)
{
    // double distance_to_corner;

    if (vars->curr_y >= 0 && vars->curr_y < data->map.rows && 
        vars->new_x >= 0 && vars->new_x < vars->row_length_cy && 
        data->map.map[vars->curr_y][vars->new_x] != '1')
        {
            // distance_to_corner = fabs(data->player.pos_y - vars->curr_y);
            // if (distance_to_corner > 0.15)
            data->player.pos_x += move_x * 0.5;
        }
        // Try Y movement only if it doesn't put us too close to the wall
    if (vars->new_y >= 0 && vars->new_y < data->map.rows && 
        vars->curr_x >= 0 && vars->curr_x < vars->row_length_y && 
        data->map.map[vars->new_y][vars->curr_x] != '1')
        {
            // distance_to_corner = fabs(data->player.pos_x - vars->curr_x);
            // if (distance_to_corner > 0.15)  
            data->player.pos_y += move_y * 0.5;
        }
}

void move_player(t_data *data, double move_x, double move_y, t_cord vars)
{
    // int blocked;
    int wall_ahead;
    int wall_x;
    int wall_y;

    vars.new_x = (int)(data->player.pos_x + move_x);
    vars.new_y = (int)(data->player.pos_y + move_y);
    vars.curr_x = (int)data->player.pos_x;
    vars.curr_y = (int)data->player.pos_y;
    vars.row_length_y = (int)ft_strlen(data->map.map[vars.new_y]);
    vars.row_length_cy = (int)ft_strlen(data->map.map[vars.curr_y]);
    // blocked = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
    //     vars.new_x >= 0 && vars.new_x < vars.row_length_y &&
    //     data->map.map[vars.new_y][vars.new_x] == '1');

    // if (blocked)
    //     diagonal_blocked(data, move_x, move_y, &vars);
    // else
    // {
    //     if (vars.curr_y >= 0 && vars.curr_y < data->map.rows && vars.new_x >= 0 
    //         && vars.new_x < vars.row_length_cy 
    //         && data->map.map[vars.curr_y][vars.new_x] != '1')
    //         data->player.pos_x += move_x;
    //     if (vars.new_y >= 0 && vars.new_y < data->map.rows && vars.curr_x >= 0 
    //         && vars.curr_x < vars.row_length_y 
    //         && data->map.map[vars.new_y][vars.curr_x] != '1')
    //         data->player.pos_y += move_y;
    // }
    wall_ahead = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
        vars.new_x >= 0 && vars.new_x < vars.row_length_y &&
        data->map.map[vars.new_y][vars.new_x] == '1');

    wall_x = (vars.curr_y >= 0 && vars.curr_y < data->map.rows && 
        vars.new_x >= 0 && vars.new_x < vars.row_length_cy &&
        data->map.map[vars.curr_y][vars.new_x] == '1');

    wall_y = (vars.new_y >= 0 && vars.new_y < data->map.rows && 
        vars.curr_x >= 0 && vars.curr_x < vars.row_length_y &&
        data->map.map[vars.new_y][vars.curr_x] == '1');
    if (wall_ahead && (!wall_x && !wall_y))
    {
        printf("Corner\n");
        return;
    }

    if (!wall_x)
        data->player.pos_x += move_x;
    if (!wall_y)
        data->player.pos_y += move_y;

}

void move_vertically(t_data *data, int direction)
{
    t_cord vars;
    double move_x;
    double move_y;

    ft_bzero(&vars, sizeof(t_cord));
    if(direction == MUP)
    {
        move_x = data->player.dir_x * MOV_SPEED;
        move_y = data->player.dir_y * MOV_SPEED;
    }
    else
    {
        move_x = -data->player.dir_x * MOV_SPEED;
        move_y = -data->player.dir_y * MOV_SPEED;
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
        move_x = data->player.plane_x * MOV_SPEED;
        move_y = data->player.plane_y * MOV_SPEED;
    }
    else
    {
        move_x = -data->player.plane_x * MOV_SPEED;
        move_y = -data->player.plane_y * MOV_SPEED;
    }
    move_player(data, move_x, move_y, vars);
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
