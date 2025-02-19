/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_dist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:27:23 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/14 13:02:36 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

t_rays	get_ray_dir(double rayangle)
{
	t_rays	dir;

	rayangle = normalize_angle(rayangle);
	dir.is_down = (rayangle > 0 && rayangle < M_PI);
	dir.is_up = !dir.is_down;
	dir.is_right = (rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI);
	dir.is_left = !dir.is_right;
	return (dir);
}

t_p	hit_hor(t_data *data, double rayangle)
{
	t_p		v;
	t_p		steps;
	t_rays	dir;
	t_p		coords;

	dir = get_ray_dir(rayangle);
	v = init_hor_pos(data, rayangle, dir);
	steps = hor_steps(rayangle, dir);
	while (v.x >= 0 && v.x <= TILE_S * data->width_map && v.y >= 0
		&& v.y <= TILE_S * data->height_map)
	{
		coords.x = floor(v.x / TILE_S);
		coords.y = floor(v.y - (dir.is_up * TILE_S)) / TILE_S;
		if (coords.y < data->height_map && coords.x < data->width_map
			&& (data->map[(int)coords.y][(int)coords.x] == '1'
			|| !door_state(data, coords, 1)))
			return (v);
		v.x += steps.x;
		v.y += steps.y;
	}
	return (v);
}

t_p	hit_vert(t_data *data, double rayangle)
{
	t_p		v;
	t_p		steps;
	t_rays	dir;
	t_p		coords;

	dir = get_ray_dir(rayangle);
	v = init_vert_pos(data, rayangle, dir);
	steps = vert_steps(rayangle, dir);
	while (v.x >= 0 && v.x <= TILE_S * data->width_map && v.y >= 0
		&& v.y <= TILE_S * data->height_map)
	{
		coords.x = (v.x - (dir.is_left * TILE_S)) / TILE_S;
		coords.y = floor(v.y / TILE_S);
		if (coords.y < data->height_map && coords.x < data->width_map
			&& (data->map[(int)coords.y][(int)coords.x] == '1'
			|| !door_state(data, coords, 1)))
			return (v);
		v.x += steps.x;
		v.y += steps.y;
	}
	return (v);
}
