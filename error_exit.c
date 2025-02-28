#include "cub3d.h"

int file_error(int id)
{
    if (id == 0)
        return (err_msg("Error: File Empty\n"));
    else if (id == -2)
    {
        // if (errno == ELOOP)
        //     return (err_msg("Error: infinite File\n"));
        perror("Error");
        return (0);
        // return (err_msg("Error: File not found\n"));
    }      
    else if (id == -1)
        return (err_msg("Error: File too large\n"));
    return (0);
}
void    destroy_imgs(t_data *data)
{
    if(data->texture.no.img)
        mlx_destroy_image(data->mlx.mlx, data->texture.no.img);
    if(data->texture.so.img)
        mlx_destroy_image(data->mlx.mlx, data->texture.so.img);
    if(data->texture.we.img)
        mlx_destroy_image(data->mlx.mlx, data->texture.we.img);
    if(data->texture.ea.img)
        mlx_destroy_image(data->mlx.mlx, data->texture.ea.img);
}