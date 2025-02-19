/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 20:24:58 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_mlx_data(t_data **data)
{
	t_mlx_data	*data_mlx;

	data_mlx = (*data)->d_mlx;
	data_mlx->mlx = mlx_init(WIDTH, HEIGHT, "Cub_3D", true);
	if (!(data_mlx->mlx))
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	data_mlx->img_map = mlx_new_image(data_mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data_mlx->mlx, data_mlx->img_map, 0, 0);
	return (0);
}

void	cleanup_and_exit(t_data **data)
{
	mlx_terminate((*data)->d_mlx->mlx);
	destory_png_textures((*data)->textures);
	gcollector(0, 0);
	exit(EXIT_SUCCESS);
}

t_p	find_plyr(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data && data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				return ((t_p){j, i});
		}
	}
	return ((t_p){0, 0});
}

int	main(int ac, char **av)
{
	int		init_mlx;
	t_data	*data;
	int		fd;

	if (ac != 2)
		return (printf("Error\nUsage: ./cub3D <map.cub>\n"), EXIT_FAILURE);
	if (!validate_file_extension(av[1]))
		return (printf("Error\nInvalid file extension\n"), EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCannot open file: %s\n", av[1]), EXIT_FAILURE);
	init_data(&data);
	if (init_data2(&data, fd))
		return (printf("Error\nInvalid map file\n"), EXIT_FAILURE);
	load_png_textures(data);
	init_mlx = init_mlx_data(&data);
	if (init_mlx)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	map_2d(&data);
	mlx_loop_hook(data->d_mlx->mlx, (void *)my_keyhook, &data);
	mlx_loop(data->d_mlx->mlx);
	cleanup_and_exit(&data);
}
