/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_p_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilot <pilot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:13:48 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/19 11:47:46 by pilot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	rot_hook(t_data *data)
{
	t_player	*player;

	player = data->player;
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_RIGHT))
		player->rotate_angle += player->rot_speed;
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_LEFT))
		player->rotate_angle -= player->rot_speed;
}

t_p	strafing(t_data *data, double movement_speed)
{
	t_p	move;

	move = (t_p){0, 0};
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_A))
	{
		move.x = -movement_speed * cos(data->player->rotate_angle + M_PI_2);
		move.y = -movement_speed * sin(data->player->rotate_angle + M_PI_2);
	}
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_D))
	{
		move.x = movement_speed * cos(data->player->rotate_angle + M_PI_2);
		move.y = movement_speed * sin(data->player->rotate_angle + M_PI_2);
	}
	return (move);
}

void	translation_hook(t_data *data)
{
	t_p		m;
	double	movement_speed;

	movement_speed = 2;
	m = (t_p){0, 0};
	m = strafing(data, movement_speed);
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_W))
	{
		m.y = movement_speed * sin(data->player->rotate_angle);
		m.x = movement_speed * cos(data->player->rotate_angle);
	}
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_S))
	{
		m.y = -movement_speed * sin(data->player->rotate_angle);
		m.x = -movement_speed * cos(data->player->rotate_angle);
	}
	if (!closed_door(&data, data->player->xc + m.x, data->player->yc + m.y)
		&& !is_wall(&data, data->player->xc + m.x, data->player->yc + m.y))
	{
		data->door_coord = (t_p){0, 0};
		data->wall_mov.x += m.x;
		data->wall_mov.y += m.y;
	}
}

void	clear_image(mlx_image_t *image, int width, int height)
{
	int	y;
	int	x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			mlx_put_pixel(image, x, y, get_rgba(0, 0, 0, 255));
	}
}

void	my_keyhook(void *param)
{
	t_data				**data;

	data = param;
	if (mlx_is_key_down((*data)->d_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*data)->d_mlx->mlx);
	sprite_hook(*data);
	door_hook(*data);
	translation_hook(*data);
	rot_hook(*data);
	mouse_hook(*data);
	clear_image((*data)->d_mlx->img_mini, MIN_WIDTH, MIN_HEIGHT);
	map_2d(data);
	walls3d(*data);
	if ((*data)->sprite.is_visible == 1 && (*data)->sprite.is_first == false)
		sprites_texture_to_image(*data);
}
