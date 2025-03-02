#include "../cub3d.h"

// static int	check_wall_collision(t_data *data, t_cord *vars)
// {
// 	int	wall_ahead;
// 	int	wall_x;
// 	int	wall_y;

// 	wall_ahead = (data->map.map[vars->new_y][vars->new_x] == '1');
// 	wall_x = (data->map.map[vars->curr_y][vars->new_x] == '1');
// 	wall_y = (data->map.map[vars->new_y][vars->curr_x] == '1');
// 	if (wall_ahead && (!wall_x && !wall_y))
// 		return (1);
// 	return (0);
// }

static int	check_bounds(t_data *data, double new_x, double new_y, t_cord *vars)
{
	int	wall_ahead;
	int	wall_x;
	int	wall_y;

	if (new_y < 0.2 || new_y >= data->map.rows - 0.2
		|| new_x < 0.2 || new_x >= vars->row_length_y - 0.2)
		return (1);
	if (vars->new_x < 0 || vars->new_x >= vars->row_length_y
	|| vars->curr_x < 0 || vars->curr_x >= vars->row_length_cy)
		return (1);
	if (data->map.map[vars->new_y][vars->new_x] == ' '
		|| data->map.map[vars->curr_y][vars->new_x] == ' '
		|| data->map.map[vars->new_y][vars->curr_x] == ' ')
		return (1);
	wall_ahead = (data->map.map[vars->new_y][vars->new_x] == '1');
	wall_x = (data->map.map[vars->curr_y][vars->new_x] == '1');
	wall_y = (data->map.map[vars->new_y][vars->curr_x] == '1');
	if (wall_ahead && (!wall_x && !wall_y))
		return (1);
	return (0);
}
static int	check_wallx(t_data *data, double new_x, double move_x, t_cord *vars)
{
	double	wall_dist_x;
	int		wall_cell_x;

	if (move_x > 0)
	{
		wall_cell_x = (int)(new_x) + 1;
		wall_dist_x = wall_cell_x - new_x;
	}
	else
	{
		wall_cell_x = (int)(new_x) - 1;
		wall_dist_x = new_x - (wall_cell_x + 1);
	}
	if ((wall_dist_x > COLLI && data->map.map[vars->curr_y][wall_cell_x] == '1')
		|| data->map.map[vars->curr_y][wall_cell_x] != '1')
		return (0);
	return (1);
}

static int	check_wally(t_data *data, double new_y, double move_y, t_cord *vars)
{
	double	wall_dist_y;
	int		wall_cell_y;

	if (move_y > 0)
	{
		wall_cell_y = (int)(new_y) + 1;
		wall_dist_y = wall_cell_y - new_y;
	}
	else
	{
		wall_cell_y = (int)(new_y) - 1;
		wall_dist_y = new_y - (wall_cell_y + 1);
	}
	if ((wall_dist_y > COLLI && data->map.map[wall_cell_y][vars->curr_x] == '1')
		|| data->map.map[wall_cell_y][vars->curr_x] != '1')
		return (0);
	return (1);
}

static void	update_position(t_data *data)
{
	static double	prev_x = -1;
	static double	prev_y = -1;
	double			dx;
	double			dy;
	double			distance;

	if (prev_x == -1)
	{
		prev_x = data->player.pos_x;
		prev_y = data->player.pos_y;
	}
	dx = data->player.pos_x - prev_x;
	dy = data->player.pos_y - prev_y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > 0.2)
	{
		data->player.pos_x = prev_x;
		data->player.pos_y = prev_y;
	}
	else
	{
		prev_x = data->player.pos_x;
		prev_y = data->player.pos_y;
	}
}

void	move_player(t_data *data, double move_x, double move_y, t_cord vars)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + move_x;
	new_y = data->player.pos_y + move_y;
	vars.new_x = (int)new_x;
	vars.new_y = (int)new_y;
	vars.curr_x = (int)data->player.pos_x;
	vars.curr_y = (int)data->player.pos_y;
	if (vars.new_y < 0 || vars.new_y >= data->map.rows
		|| vars.curr_y < 0 || vars.curr_y >= data->map.rows)
		return ;
	vars.row_length_y = (int)ft_strlen(data->map.map[vars.new_y]);
	vars.row_length_cy = (int)ft_strlen(data->map.map[vars.curr_y]);
	if (check_bounds(data, new_x, new_y, &vars))
		return ;
	if (data->map.map[vars.curr_y][vars.new_x] != '1'
		&& !check_wallx(data, new_x, move_x, &vars))
		data->player.pos_x += move_x ;
	if (data->map.map[vars.new_y][vars.curr_x] != '1'
		&& !check_wally(data, new_y, move_y, &vars))
		data->player.pos_y += move_y ;
	update_position(data);
}
