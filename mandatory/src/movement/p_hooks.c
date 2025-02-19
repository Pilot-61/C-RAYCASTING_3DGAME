/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:13:48 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/13 17:42:11 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	rot_hook(t_data *data)
{
	t_player	*player;

	player = data->player;
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_RIGHT))
		player->rotate_angle += player->rot_speed;
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_LEFT))
		player->rotate_angle -= player->rot_speed;
}

t_p	strafing(t_data *data, float movement_speed)
{
	t_p	move;

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
	t_p		move;
	float	movement_speed;

	movement_speed = 2;
	move = (t_p){0, 0};
	move = strafing(data, movement_speed);
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_W))
	{
		move.y = movement_speed * sin(data->player->rotate_angle);
		move.x = movement_speed * cos(data->player->rotate_angle);
	}
	if (mlx_is_key_down(data->d_mlx->mlx, MLX_KEY_S))
	{
		move.y = -movement_speed * sin(data->player->rotate_angle);
		move.x = -movement_speed * cos(data->player->rotate_angle);
	}
	if (!is_wall(&data, data->player->xc + move.x, data->player->yc + move.y))
	{
		data->wall_mov.x += move.x;
		data->wall_mov.y += move.y;
	}
}

void	my_keyhook(void *param)
{
	t_data	**data;

	data = param;
	if (mlx_is_key_down((*data)->d_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*data)->d_mlx->mlx);
	translation_hook(*data);
	rot_hook(*data);
	map_2d(data);
	walls3d(*data);
}
