/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:14:52 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/13 16:38:17 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	draw_rays(t_data *data)
{
	int		r_id;
	float	angle;
	float	rayangle;
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
		data->d_rays[r_id].rayangle = rayangle;
		rayangle += angle / WIDTH;
	}
}
