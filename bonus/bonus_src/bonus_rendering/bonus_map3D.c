/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:55:45 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/14 14:10:12 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

t_line	ft_init_wall_line(int i, double wall_height)
{
	t_line	line;
	t_p		top;
	t_p		bottom;

	top.x = i;
	top.y = (HEIGHT / 2) - (wall_height / 2);
	bottom.x = i;
	bottom.y = top.y + wall_height;
	if (top.x < MIN_WIDTH && top.y < MIN_HEIGHT)
		top.y = MIN_HEIGHT;
	line.p0 = top;
	line.p1 = bottom;
	return (line);
}

double	ft_calculate_wall_height(t_data *data, int i)
{
	double	distance;
	double	dist_proj;
	double	wall_height;

	distance = data->d_rays[i].raydist
		* cos(data->d_rays[i].rayangle - data->player->rotate_angle);
	dist_proj = (WIDTH / 2) / tan(30 * (M_PI / 180));
	wall_height = (TILE_S / distance) * dist_proj;
	return (wall_height);
}

void	ft_draw_ceiling(t_data *data, int i, double start_y)
{
	t_line	line;
	int		ceiling;

	ceiling = 0;
	if (i < MIN_WIDTH && ceiling < MIN_HEIGHT)
		ceiling = MIN_HEIGHT;
	line.p0 = (t_p){i, ceiling};
	line.p1 = (t_p){i, start_y};
	line.color = data->colors->c_ceiling;
	draw_line(data, data->d_mlx->img_map, line);
}

void	ft_draw_floor(t_data *data, int i, t_p end_y)
{
	t_line	line;

	line.p0 = end_y;
	line.p1 = (t_p){i, HEIGHT};
	line.color = data->colors->c_floor;
	draw_line(data, data->d_mlx->img_map, line);
}
