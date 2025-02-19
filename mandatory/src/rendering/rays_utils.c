/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:36:13 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/11 11:55:25 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_p	ray_dist(t_data *data, float rayangle, t_p p1, int r_id)
{
	float	dis_h;
	float	dis_v;
	t_p		ph;
	t_p		pv;

	data->d_rays[r_id].hit_hor = 0;
	data->d_rays[r_id].hit_vert = 0;
	ph = hit_hor(data, rayangle);
	pv = hit_vert(data, rayangle);
	dis_h = sqrt((p1.x - ph.x) * (p1.x - ph.x) + (p1.y - ph.y) * (p1.y - ph.y));
	dis_v = sqrt((p1.x - pv.x) * (p1.x - pv.x) + (p1.y - pv.y) * (p1.y - pv.y));
	if (dis_h < dis_v)
	{
		data->d_rays[r_id].hit = ph;
		data->d_rays[r_id].raydist = dis_h;
		data->d_rays[r_id].hit_hor = 1;
		return (ph);
	}
	else
	{
		data->d_rays[r_id].hit = pv;
		data->d_rays[r_id].raydist = dis_v;
		data->d_rays[r_id].hit_vert = 1;
		return (pv);
	}
}

t_p	vert_steps(float rayangle, t_rays dir)
{
	t_p	steps;

	steps.x = TILE_S;
	if (dir.is_left)
		steps.x *= -1;
	steps.y = TILE_S * tan(rayangle);
	if (dir.is_up && steps.y > 0)
		steps.y *= -1;
	if (dir.is_down && steps.y < 0)
		steps.y *= -1;
	return (steps);
}

t_p	init_vert_pos(t_data *data, float rayangle, t_rays dir)
{
	t_p	v;

	v.x = floor(data->player->xc / TILE_S) * TILE_S;
	if (dir.is_right)
		v.x += TILE_S;
	v.y = data->player->yc + (v.x - data->player->xc) * tan(rayangle);
	return (v);
}

t_p	hor_steps(float rayangle, t_rays dir)
{
	t_p	steps;

	steps.y = TILE_S;
	if (dir.is_up)
		steps.y *= -1;
	steps.x = TILE_S / tan(rayangle);
	if (dir.is_left && steps.x > 0)
		steps.x *= -1;
	if (dir.is_right && steps.x < 0)
		steps.x *= -1;
	return (steps);
}

t_p	init_hor_pos(t_data *data, float rayangle, t_rays dir)
{
	t_p	v;

	v.y = floor(data->player->yc / TILE_S) * TILE_S;
	if (dir.is_down)
		v.y += TILE_S;
	v.x = data->player->xc + (v.y - data->player->yc) / tan(rayangle);
	return (v);
}
