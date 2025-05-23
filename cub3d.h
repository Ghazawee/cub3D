/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbasheer <hbasheer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:10:24 by hbasheer          #+#    #+#             */
/*   Updated: 2025/03/04 19:10:25 by hbasheer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# if __APPLE__
#  include "mlx_mac/mlx.h"
# elif __linux__
#  include "mlx_linux/mlx.h"
# endif

# if __APPLE__
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define RIGHT_ARROW 124
#  define LEFT_ARROW 123
# elif __linux__
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define RIGHT_ARROW 65363
#  define LEFT_ARROW 65361
# endif
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TEX_SIZE 64
# define MOV_SPEED 2.0
# define ROT_SPEED 0.7
# define COLLI 0.15
# define MLEFT 0
# define MRIGHT 1
# define MUP 1
# define MDOWN 0
# define R_ROTATE 1
# define L_ROTATE 0
# define MAX_BYTES 102400

typedef struct s_vars
{
	int				i;
	int				j;
	int				k;
}					t_vars;

typedef struct s_cord
{
	int				row_length_y;
	int				row_length_cy;
	int				new_x;
	int				new_y;
	int				curr_y;
	int				curr_x;
}					t_cord;

typedef struct s_draw
{
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
}					t_draw;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			wallx;
	int				line_height;
	int				tex_num;
}					t_ray;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_elements
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor;
	int				ceiling;
	int				all_parsed;
}					t_elements;

typedef struct s_map
{
	char			*fullcub;
	char			**cmap;
	char			**map;
	int				rows;
	int				cols;
	int				p_x;
	int				p_y;
	char			direction;
}					t_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_image			img;
}					t_mlx;

typedef struct s_textures
{
	t_image			no;
	t_image			so;
	t_image			we;
	t_image			ea;
}					t_textures;

typedef struct s_data
{
	t_elements		elements;
	t_mlx			mlx;
	t_map			map;
	t_player		player;
	t_image			image;
	t_ray			ray;
	t_textures		texture;
	double			delta_time;
	struct timeval	last;
	bool			keys[7];
}					t_data;

typedef struct s_draw_walls
{
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				colour;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	t_image			*current_tex;
	double			step;
	double			tex_pos;
}					t_draw_walls;

void				fr_array(char **array);
void				free_data(t_data *data);
int					validate_map(t_map *map, t_data *data);
int					err_msg(char *msg);
char				*get_next_line(int fd);
void				my_mlx_pixel_put(t_image *img, int x, int y, int color);
int					file_error(int id);
//------------------------------------------------------//
//-----------------------Parsing-----------------------//
//------------------------------------------------------//
//-----------------------parse.c---------------------//
int					parse_elem_map(char *file, t_data *data);
//-----------------------utils-----------------------//
void				free_str(char **str);
int					only_spaces(char *str);
void				init_vars(t_vars *vars);
int					err_msg(char *msg);
int					check_multiple_commas(char *str);
//-----------------------par_elem----------------------//
int					store_elem(t_elements *elem, char *line);

//----------------------validate_map----------------------//
int					validate_map(t_map *map, t_data *data);

//----------------------tex_map_utils----------------------//
int					copy_map(t_map *map, int start);
int					assign_tex(char **tex, char *trim);
int					check_file(char *file);
//----------------------map_utils----------------------//
int					top_bot_row(char *line);
void				calculate_map_rows(t_map *map);
int					validate_map_walls(t_map *map, t_vars vars);
int					validate_map_chars(t_map *map, t_vars vars);
int					empty_line(char *str);
//------------------------------------------------------//
//-----------------------Execution-----------------------//
//------------------------------------------------------//
//------------------handle_actions.c----------------//
int					key_events(int keycode, t_data *data);
int					exit_window(t_data *data);
int					render_frames(t_data *data);
void				move_player(t_data *data, double move_x, double move_y,
						t_cord vars);
void				move_horizontally(t_data *data, int direction);
void				move_vertically(t_data *data, int direction);
void				rotate(t_player *pl, int direction, t_data *data);
void				colour_floor_ceiling(t_data *data);
void				draw_walls(t_ray *ray, t_data *data, int x);
void				destroy_imgs(t_data *data);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
void				check_movement(t_data *data);
void				cast_rays(t_ray *ray, t_player *player, t_data *data);
void				init_step_side(t_ray *ray, t_player *player, t_data *data);
void				dda_algo(t_ray *ray, t_data *data);

//------------------init_data.c----------------//
void				init_data(t_data *data);
void				init_player(t_data *data);
void				init_texture(t_data *data);
void				mlx_loops_hooks(t_data *data);

#endif