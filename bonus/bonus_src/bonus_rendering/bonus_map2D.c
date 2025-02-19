/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map2D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilot <pilot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:27:44 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/19 11:42:14 by pilot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

bool	is_wall(t_data **data, int x, int y)
{
	char	**map;
	t_p		p_i;
	double	r;

	r = (*data)->player->r;
	map = (*data)->map;
	if (!map)
		return (true);
	p_i.x = floor(x / TILE_S);
	p_i.y = floor(y / TILE_S);
	if (p_i.x < 0 || p_i.y < 0
		|| p_i.y >= (*data)->height_map || p_i.x >= (*data)->width_map)
		return (true);
	if (map[(int)floor((y + r) / TILE_S)][(int)floor(x / TILE_S)] == '1')
		return (true);
	else if (map[(int)floor((y - r) / TILE_S)][(int)floor((x) / TILE_S)] == '1')
		return (true);
	else if (map[(int)floor(y / TILE_S)][(int)floor((x - r) / TILE_S)] == '1')
		return (true);
	else if (map[(int)floor((y) / TILE_S)][(int)floor((x + r) / TILE_S)] == '1')
		return (true);
	return (false);
}

bool	closed_door(t_data **data, int x, int y)
{
	t_p		door;
	int		i;

	door = (t_p){floor(x / TILE_S), floor(y / TILE_S)};
	i = -1;
	if (door.x < 0 || door.y < 0
		|| door.y >= (*data)->height_map || door.x >= (*data)->width_map)
		return (true);
	while ((*data)->t_doors[++i])
	{
		if ((*data)->t_doors[i]->pos.y == (int)floor((y + 2) / TILE_S)
			&& (*data)->t_doors[i]->pos.x == (int)floor(x / TILE_S))
			return (!(*data)->t_doors[i]->state);
		else if ((*data)->t_doors[i]->pos.y == (int)floor((y - 2) / TILE_S)
			&& (*data)->t_doors[i]->pos.x == (int)floor(x / TILE_S))
			return (!(*data)->t_doors[i]->state);
		else if ((*data)->t_doors[i]->pos.y == (int)floor((y) / TILE_S)
			&& (*data)->t_doors[i]->pos.x == (int)floor((x - 2) / TILE_S))
			return (!(*data)->t_doors[i]->state);
		else if ((*data)->t_doors[i]->pos.y == (int)floor((y) / TILE_S)
			&& (*data)->t_doors[i]->pos.x == (int)floor((x + 2) / TILE_S))
			return (!(*data)->t_doors[i]->state);
	}
	return (false);
}

void	draw_player(t_data **data, t_player *player, int color)
{
	t_line	line;
	double	rayangle;
	int		i;

	player->xc = player->x_pos + TILE_S / 2 + (*data)->wall_mov.x;
	player->yc = player->y_pos + TILE_S / 2 + (*data)->wall_mov.y;
	draw_rays(*data);
	rayangle = (*data)->player->rotate_angle + M_PI;
	line.color = color;
	i = 0;
	while (++i < TILE_S - 4)
	{
		line.p0.x = (*data)->plyr_cntr.x + cos(rayangle + 0.3) * i;
		line.p1.x = (*data)->plyr_cntr.x + cos(rayangle - 0.3) * i;
		line.p1.y = (*data)->plyr_cntr.y + sin(rayangle - 0.3) * i;
		line.p0.y = (*data)->plyr_cntr.y + sin(rayangle + 0.3) * i;
		draw_line(*data, (*data)->d_mlx->img_mini, line);
	}
}

void	draw_mini_map(t_data **data, int i, int j, t_p point)
{
	int	color;
	int	door;

	if ((*data)->colors->c_floor == 255)
		color = get_rgba(140, 79, 81, 255);
	else
		color = (*data)->colors->c_floor;
	if (!door_state(*data, (t_p){j, i}, 0))
		door = get_rgba(30, 30, 30, 255);
	else
		door = color - 100;
	if ((*data)->map[i][j] == '1')
		draw_square(*data, point.x, point.y, 255);
	else if ((*data)->map[i][j] == '0')
		draw_square(*data, point.x, point.y, color);
	else if ((*data)->map[i][j] == 'D')
		draw_square(*data, point.x, point.y, door);
	else
	{
		(*data)->player->x_pos = (*data)->wall_pos.x;
		(*data)->player->y_pos = (*data)->wall_pos.y;
		draw_square(*data, point.x, point.y, color);
	}
}

void	map_2d(t_data **data)
{
	int	i;
	int	j;
	t_p	point;

	point.y = (*data)->offs.y - (*data)->wall_mov.y;
	(*data)->wall_pos.y = 0;
	i = -1;
	while ((*data)->map[++i])
	{
		point.x = (*data)->offs.x - (*data)->wall_mov.x;
		(*data)->wall_pos.x = 0;
		j = -1;
		while ((*data) && (*data)->map[i][++j])
		{
			draw_mini_map(data, i, j, point);
			point.x += TILE_S;
			(*data)->wall_pos.x += TILE_S;
		}
		point.y += TILE_S;
		(*data)->wall_pos.y += TILE_S;
	}
	draw_player(data, (*data)->player, get_rgba(255, 255, 255, 255));
}
