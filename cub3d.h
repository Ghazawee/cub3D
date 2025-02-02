#ifndef CUB3D_H
# define CUB3D_H
#include "libft/libft.h"
//#include "gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>

typedef struct s_vars
{
    int		i;
    int		j;
    int     k;
    int     fd;
    int     ret;
    char   *tmp;
    char    *line;
}t_vars;

typedef struct s_ray
{}t_ray;

typedef struct s_image
{

}t_image;

typedef struct s_player
{}t_player;

typedef struct s_elements
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int      floor;
    int      ceiling;
    int      all_parsed;
}t_elements;

typedef struct s_map
{
    char    *fullcub;
    char    **cmap;
    char    **map;
    int     rows;
    int     cols;
    int     p_x;
    int     p_y;
    char    direction;
}t_map;

typedef struct s_data
{
    t_elements  elements;
    t_map       map;
    t_player    player;
    t_image     image;
    t_ray       ray;
}t_data;

void	fr_array(char **array);

int	validate_map(t_map *map, t_data *data);
int err_msg(char *msg);
char	*get_next_line(int fd);

//------------------------------------------------------//
//-----------------------Parsing-----------------------//
//------------------------------------------------------//
//-----------------------parse.c---------------------//
int parse_elem_map(char *file, t_data *data);
//-----------------------utils-----------------------//
void    free_str(char **str);
int	only_spaces(char *str);
void init_vars(t_vars *vars);
int err_msg(char *msg);
//-----------------------par_elem----------------------//
int store_elem(t_elements *elem, char *line);

//----------------------validate_map----------------------//
int	validate_map(t_map *map, t_data *data);

//----------------------map_utils----------------------//
int top_bot_row(char *line);
void calculate_map_rows(t_map *map);

#endif