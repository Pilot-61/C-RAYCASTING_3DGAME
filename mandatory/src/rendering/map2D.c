/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:27:44 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/13 16:22:14 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

void	draw_player(t_data **data, t_player *player)
{
	player->xc = player->x_pos + TILE_S / 2 + (*data)->wall_mov.x;
	player->yc = player->y_pos + TILE_S / 2 + (*data)->wall_mov.y;
	draw_rays(*data);
}

void	map_2d(t_data **data)
{
	int	i;
	int	j;

	(*data)->wall_pos.y = 0;
	i = -1;
	while ((*data)->map[++i])
	{
		(*data)->wall_pos.x = 0;
		j = -1;
		while ((*data) && (*data)->map[i][++j])
		{
			if ((*data)->map[i][j] != '1' && (*data)->map[i][j] != '0')
			{
				(*data)->player->x_pos = (*data)->wall_pos.x;
				(*data)->player->y_pos = (*data)->wall_pos.y;
			}
			(*data)->wall_pos.x += TILE_S;
		}
		(*data)->wall_pos.y += TILE_S;
	}
	draw_player(data, (*data)->player);
}
