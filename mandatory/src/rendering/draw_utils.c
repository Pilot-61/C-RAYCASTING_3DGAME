/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:25:46 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/14 21:08:46 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_line(t_line *line, t_draw *draw, t_data *data, mlx_image_t *image)
{
	t_p	limit;

	limit = (t_p){MIN_WIDTH, MIN_HEIGHT};
	if (image == data->d_mlx->img_map)
		limit = (t_p){WIDTH, HEIGHT};
	draw->limit = limit;
	line->p0.x = floor(line->p0.x);
	line->p0.y = floor(line->p0.y);
	line->p1.x = floor(line->p1.x);
	line->p1.y = floor(line->p1.y);
	draw->dx = fabs(line->p1.x - line->p0.x);
	draw->sx = -1;
	if (line->p0.x < line->p1.x)
		draw->sx = 1;
	draw->dy = -fabs(line->p1.y - line->p0.y);
	draw->sy = -1;
	if (line->p0.y < line->p1.y)
		draw->sy = 1;
	draw->decis = draw->dx + draw->dy;
}

void	draw_line(t_data *data, mlx_image_t *image, t_line line)
{
	t_draw	draw;
	int		e2;

	init_line(&line, &draw, data, image);
	while (1)
	{
		if ((line.p0.x >= 0 && line.p0.y >= 0)
			&& (line.p0.x < draw.limit.x && line.p0.y < draw.limit.y))
			mlx_put_pixel(image, line.p0.x, line.p0.y, line.color);
		e2 = 2 * draw.decis;
		if (e2 >= draw.dy)
		{
			if (line.p0.x == line.p1.x)
				break ;
			draw.decis = draw.decis + draw.dy;
			line.p0.x = line.p0.x + draw.sx;
		}
		if (e2 <= draw.dx)
		{
			if (line.p0.y == line.p1.y)
				break ;
			draw.decis = draw.decis + draw.dx;
			line.p0.y = line.p0.y + draw.sy;
		}
	}
}
