/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:45:05 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 20:09:22 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	sprites_texture_to_image(t_data *data)
{
	static int	i;
	int			img_width;
	int			img_height;

	if (data->sprite.img)
		mlx_delete_image(data->d_mlx->mlx, data->sprite.img);
	data->sprite.img = mlx_texture_to_image(data->d_mlx->mlx,
			data->sprite.texture[i]);
	img_height = data->sprite.texture[i]->height;
	img_width = data->sprite.texture[i]->width;
	if (data->sprite.img)
		mlx_image_to_window(data->d_mlx->mlx, data->sprite.img,
			0, 0);
	i++;
	if (i == 340)
	{
		i = 0;
		data->sprite.is_visible = 0;
	}
}

void	check_fsprite(t_data **data, mlx_image_t	**first_img)
{
	int					img_width;
	int					img_height;

	if ((*data)->sprite.is_first)
	{
		img_height = (*data)->sprite.texture[0]->height;
		img_width = (*data)->sprite.texture[0]->width;
		*first_img = mlx_texture_to_image((*data)->d_mlx->mlx,
				(*data)->sprite.texture[0]);
		mlx_image_to_window((*data)->d_mlx->mlx, *first_img,
			(WIDTH - img_width) / 2, HEIGHT - img_height);
		(*data)->sprite.is_first = false;
	}
}
