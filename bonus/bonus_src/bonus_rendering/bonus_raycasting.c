/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:52 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/13 16:38:22 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	door_hit(t_data *data, t_p visible_d, int r_id, double angle)
{
	if (data->d_rays[r_id].hit_hor)
	{
		visible_d.x = floor(visible_d.x / TILE_S);
		visible_d.y = floor(visible_d.y
				- (get_ray_dir(angle).is_up * TILE_S)) / TILE_S;
	}
	else
	{
		visible_d.x = floor(visible_d.x
				- (get_ray_dir(angle).is_left * TILE_S)) / TILE_S;
		visible_d.y = floor(visible_d.y / TILE_S);
	}
	if (data->map[(int)visible_d.y][(int)visible_d.x] == 'D')
		data->d_rays[r_id].hit_door = true;
	else
		data->d_rays[r_id].hit_door = false;
}

void	draw_rays(t_data *data)
{
	int		r_id;
	double	angle;
	double	rayangle;
	t_line	line;

	r_id = -1;
	angle = 60 * (M_PI / 180);
	rayangle = data->player->rotate_angle - (angle / 2);
	line.color = get_rgba(255, 0, 0, 255);
	while (++r_id < WIDTH)
	{
		line.p0.x = data->player->xc;
		line.p0.y = data->player->yc;
		line.p1.x = data->player->xc + cos(rayangle) * MIN_WIDTH;
		line.p1.y = data->player->yc + sin(rayangle) * MIN_HEIGHT;
		line.p1 = ray_dist(data, rayangle, line.p0, r_id);
		door_hit(data, line.p1, r_id, rayangle);
		data->d_rays[r_id].rayangle = rayangle;
		rayangle += angle / WIDTH;
	}
}
