/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:43:03 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/11 11:54:44 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	choose_color(t_data *data, int i)
{
	int	color;

	color = 0;
	if (data->d_rays[i].direction == 'N')
		color = get_rgba(255, 90, 90, 255);
	else if (data->d_rays[i].direction == 'S')
		color = get_rgba(106, 90, 205, 255);
	else if (data->d_rays[i].direction == 'E')
		color = get_rgba(0, 0, 255, 255);
	else if (data->d_rays[i].direction == 'W')
		color = get_rgba(60, 179, 113, 255);
	return (color);
}

void	ray_dire(t_data *data, int r_id)
{
	t_rays	ray;

	ray = get_ray_dir(data->d_rays[r_id].rayangle);
	if (data->d_rays[r_id].hit_hor)
	{
		if (ray.is_down)
			data->d_rays[r_id].direction = 'S';
		else if (ray.is_up)
			data->d_rays[r_id].direction = 'N';
	}
	else if (data->d_rays[r_id].hit_vert)
	{
		if (ray.is_left)
			data->d_rays[r_id].direction = 'W';
		else if (ray.is_right)
			data->d_rays[r_id].direction = 'E';
	}
}
