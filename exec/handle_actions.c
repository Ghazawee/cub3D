#include "../cub3d.h"

void exit_window(t_data *data)
{
    free_data(data);
    free(data->mlx.mlx);
    mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    free(data->mlx.win);
    exit(0);
}

void key_events(int keycode, t_data *data)
{
    if (keycode == 65307)
        exit_window(data);
    if (keycode == 119)
        move_forward(data); // can make it one function and send flag same for others
    if (keycode == 115)
        move_backward(data);
    if (keycode == 97)
        move_left(data);
    if (keycode == 100)
        move_right(data);
    if (keycode == 65361)
        rotate_left(data);
    if (keycode == 65363)
        rotate_right(data);
}
