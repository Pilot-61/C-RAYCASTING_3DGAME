/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:35:02 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 20:38:44 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	door_hook(t_data *data)
{
	t_doors	**doors;
	int		i;

	doors = data->t_doors;
	i = -1;
	while (doors[++i])
	{
		if (doors[i]->seen)
		{
			if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_C))
				doors[i]->state = false;
			if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_O))
				doors[i]->state = true;
		}
		doors[i]->seen = false;
	}
}

void	mouse_hook(t_data *data)
{
	static int	old_mouse_x = 0;
	int			mouse_x;
	int			mouse_y;
	int			delta;

	mlx_set_cursor_mode(data->d_mlx->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(data->d_mlx->mlx, &mouse_x, &mouse_y);
	delta = mouse_x - old_mouse_x;
	if (delta > 0)
		data->player->rotate_angle += data->player->rot_speed;
	if (delta < 0)
		data->player->rotate_angle -= data->player->rot_speed;
	old_mouse_x = mouse_x;
}

void	sprite_hook(t_data *data)
{
	static mlx_image_t	*first_img;

	check_fsprite(&data, &first_img);
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_M))
	{
		if (first_img)
		{
			mlx_delete_image(data->d_mlx->mlx, first_img);
			first_img = NULL;
		}
		data->sprite.is_visible = 1;
	}
}
