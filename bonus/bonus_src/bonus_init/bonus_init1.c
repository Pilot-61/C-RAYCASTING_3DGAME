/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:39:17 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/13 16:11:43 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	init_data(t_data **data)
{
	*data = gcollector(sizeof(t_data), 1);
	(*data)->colors = gcollector(sizeof(t_colors), 1);
	(*data)->d_mlx = gcollector(sizeof(t_mlx_data), 1);
	(*data)->textures = gcollector(sizeof(t_textures), 1);
	(*data)->d_rays = gcollector(sizeof(t_rays) * WIDTH, 1);
	(*data)->map = NULL;
	(*data)->player = gcollector(sizeof(t_player), 1);
	ft_memset(&(*data)->md, 0, sizeof(t_md));
	ft_memset((*data)->textures, 0, sizeof(t_textures));
	(*data)->md.normalized_map = NULL;
	(*data)->colors->f_red = -1;
	(*data)->colors->f_green = -1;
	(*data)->colors->f_blue = -1;
	(*data)->colors->c_red = -1;
	(*data)->colors->c_green = -1;
	(*data)->colors->c_blue = -1;
	(*data)->wall = false;
	(*data)->player->rotate_angle = M_PI;
	(*data)->player->rot_speed = 5 * (M_PI / 180);
	(*data)->player->r = TILE_S / 4;
	(*data)->sprite.is_visible = 0;
	(*data)->md.player_count = 0;
}

void	delete_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < 340)
	{
		if (data->sprite.texture[i])
			mlx_delete_texture(data->sprite.texture[i]);
		i++;
	}
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
	if (textures->door)
		mlx_delete_texture(textures->door);
}

int	load_png_textures(t_data *data)
{
	data->textures->no_texture = mlx_load_png(data->textures->no);
	data->textures->so_texture = mlx_load_png(data->textures->so);
	data->textures->we_texture = mlx_load_png(data->textures->we);
	data->textures->ea_texture = mlx_load_png(data->textures->ea);
	data->textures->door = mlx_load_png("images/doors/door1.png");
	if (!data->textures->no_texture || !data->textures->so_texture
		|| !data->textures->we_texture || !data->textures->ea_texture
		|| !data->textures->door)
		error();
	return (0);
}
