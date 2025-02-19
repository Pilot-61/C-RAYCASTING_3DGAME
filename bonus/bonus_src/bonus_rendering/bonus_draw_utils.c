/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_draw_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:25:46 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/16 19:56:03 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

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

void	draw_square(t_data *data, int x, int y, long color)
{
	t_line	line;

	line.p0.x = x;
	line.p0.y = y;
	line.p1.y = y;
	line.p1.x = x + TILE_S;
	line.color = color;
	while (line.p1.y < (y + TILE_S))
	{
		draw_line(data, data->d_mlx->img_mini, line);
		line.p0.y++;
		line.p1.y++;
	}
}

bool	door_state(t_data *data, t_p visible_d, bool get_distance)
{
	int		i;
	t_doors	**doors;
	t_p		plyr_i;
	double	distance;

	plyr_i.x = floor(data->player->xc / TILE_S);
	plyr_i.y = floor(data->player->yc / TILE_S);
	doors = data->t_doors;
	i = -1;
	distance = 0;
	if (get_distance)
		distance = fabs(plyr_i.x - visible_d.x) + fabs(plyr_i.y - visible_d.y);
	while (doors && doors[++i])
	{
		if (visible_d.x == doors[i]->pos.x && visible_d.y == doors[i]->pos.y)
		{
			if (distance > 0 && distance < 3)
				doors[i]->seen = true;
			if (!doors[i]->state)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}
