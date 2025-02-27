#include "cub3d.h"

int file_error(int id)
{
    if (id == 0)
        return (err_msg("Error: File Empty\n"));
    else if (id == -2)
        return (err_msg("Error: File not found\n"));
    else if (id == -1)
        return (err_msg("Error: File too large\n"));
    return (0);
}