#ifndef CUB3D_H
# define CUB3D_H
#include "libft/libft.h"
#include "mlx_mac/mlx.h"
//#include "gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>
#include <math.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TEX_SIZE 64
# define MOV_SPEED 0.1
# define ROT_SPEED 0.1
# define MLEFT 0
# define MRIGHT 1
# define MUP 1
# define MDOWN 0
# define R_ROTATE 1
# define L_ROTATE 0

typedef struct s_vars
{
    int		i;
    int		j;
    int     k;
    int     c;
    int     fd;
    int     ret;
    char   *tmp;
    char    *line;
}t_vars;

typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
}t_ray;

typedef struct s_image
{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
}t_image;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}t_player;

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

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_image img;
}t_mlx;

typedef struct s_data
{
    t_elements  elements;
    t_mlx       mlx;
    t_map       map;
    t_player    player;
    t_image     image;
    t_ray       ray;
}t_data;

void	fr_array(char **array);
void free_data(t_data *data);
int	validate_map(t_map *map, t_data *data);
int err_msg(char *msg);
char	*get_next_line(int fd);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);

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

//------------------------------------------------------//
//-----------------------Execution-----------------------//
//------------------------------------------------------//
//------------------handle_actions.c----------------//
int key_events(int keycode, t_data *data);
int exit_window(t_data *data);
int    render_frames(t_data *data);

void draw_gmap(t_map *map, t_vars *v, t_data *data);
void draw_player(t_player *player, t_vars *v, t_data *data);
#endif