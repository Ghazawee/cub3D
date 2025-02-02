#include "cub3d.h"

// void	fr_array(char ***arr)
// {
//     int i;

// 	i = 0;
//     if (arr && *arr)
//     {
//         while ((*arr)[i])
//         {
//             free((*arr)[i]);
//             (*arr)[i] = NULL;
//             i++;
//         }
//         free(*arr);
//         *arr = NULL;
//     }
// }

void	fr_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i]=NULL;
		i++;
	}
	free(array);
	array = NULL;
}
void free_data(t_data *data)
{
	free(data->map.fullcub);
	if(data->map.cmap)
		fr_array(data->map.cmap);
	free(data->elements.no);
	free(data->elements.so);
	free(data->elements.we);
	free(data->elements.ea);
}

void	init_data(t_data *data)
{
	ft_bzero(&data->elements, sizeof(t_elements));
	ft_bzero(&data->map, sizeof(t_map));
	// ft_bzero(&data->player, sizeof(t_player));
	// ft_bzero(&data->image, sizeof(t_image));
	// ft_bzero(&data->ray, sizeof(t_ray));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		write(2, "Error: Invalid number of arguments\n", 36);
		return (1); 
	}
	if(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		write(2, "Error: Invalid file extension\n", 30);
		return (1);
	}
	printf("file: %s valid\n", av[1]);
	init_data(&data);
	parse_elem_map(av[1], &data);
	free_data(&data);
	// free(data.map.fullcub);
	// fr_array(data.map.cmap);
	// free(data.elements.no);
	// free(data.elements.so);
	// free(data.elements.we);
	// free(data.elements.ea);
}
