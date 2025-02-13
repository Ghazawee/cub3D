#include "../cub3d.h"

void init_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->c = 0;
	vars->fd = -1;
	vars->ret = 0;
	vars->line = NULL;
	vars->tmp = NULL;
}

int	only_spaces(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13)) // add new line??
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

void free_str(char **str)
{
    if (str && *str)
    {
        free(*str);
        *str = NULL;
    }
}

int err_msg(char *msg)
{
	while(*msg)
		write(2, msg++, 1);
	return (0);
}
int check_multiple_commas(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == ',')
		{
			if(!str[i + 1]  || (str[i +1] && str[i + 1] == ','))
				return (-1);
		}
		i++;
	}
	return (0);
}