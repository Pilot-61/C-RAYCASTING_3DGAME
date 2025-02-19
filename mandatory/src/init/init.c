/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:54:13 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 21:12:59 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	error(void)
{
	char	*err;

	err = ft_strdup(mlx_strerror(mlx_errno));
	printf("Error\n%s\n", err);
	exit(EXIT_FAILURE);
}

void	init_data(t_data **data)
{
	*data = gcollector(sizeof(t_data), 1);
	(*data)->colors = gcollector(sizeof(t_colors), 1);
	(*data)->d_mlx = gcollector(sizeof(t_mlx_data), 1);
	(*data)->textures = gcollector(sizeof(t_textures), 1);
	(*data)->d_rays = gcollector(sizeof(t_rays) * WIDTH, 1);
	(*data)->map = NULL;
	(*data)->player = gcollector(sizeof(t_player), 1);
	memset(&(*data)->md, 0, sizeof(t_md));
	memset((*data)->textures, 0, sizeof(t_textures));
	(*data)->colors->f_red = -1;
	(*data)->colors->f_green = -1;
	(*data)->colors->f_blue = -1;
	(*data)->colors->c_red = -1;
	(*data)->colors->c_green = -1;
	(*data)->colors->c_blue = -1;
	(*data)->player->rotate_angle = M_PI;
	(*data)->player->rot_speed = 2 * (M_PI / 180);
	(*data)->player->r = TILE_S / 4;
}

int	init_data2(t_data **data, int fd)
{
	if (parse_file(fd, *data))
	{
		close(fd);
		gcollector(0, 0);
		return (1);
	}
	(*data)->map = duplicate_map((*data)->md.normalized_map,
			(*data)->md.height, (*data)->md.width);
	(*data)->height_map = (*data)->md.height;
	(*data)->width_map = (*data)->md.width;
	(*data)->player->pos = (t_p){MIN_WIDTH / 2, MIN_HEIGHT / 2};
	(*data)->wall_mov = (t_p){0, 0};
	return (0);
}

void	load_png_textures(t_data *data)
{
	data->textures->no_texture = mlx_load_png(data->textures->no);
	data->textures->so_texture = mlx_load_png(data->textures->so);
	data->textures->we_texture = mlx_load_png(data->textures->we);
	data->textures->ea_texture = mlx_load_png(data->textures->ea);
	if (!data->textures->no_texture || !data->textures->so_texture
		|| !data->textures->we_texture || !data->textures->ea_texture)
		error();
}

void	destory_png_textures(t_textures *textures)
{
	if (textures->no_texture)
		mlx_delete_texture(textures->no_texture);
	if (textures->so_texture)
		mlx_delete_texture(textures->so_texture);
	if (textures->we_texture)
		mlx_delete_texture(textures->we_texture);
	if (textures->ea_texture)
		mlx_delete_texture(textures->ea_texture);
}
