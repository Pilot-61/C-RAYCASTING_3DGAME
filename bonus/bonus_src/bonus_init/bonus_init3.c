/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:22:24 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 20:23:58 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	init_data2(t_data **data, int fd)
{
	if (parse_file(fd, *data))
	{
		close(fd);
		gcollector(0, 0);
		return (1);
	}
	(*data)->map = duplicate_map((*data)->md.normalized_map,
			(*data)->md.height, (*data)->md.width);
	(*data)->height_map = (*data)->md.height;
	(*data)->width_map = (*data)->md.width;
	(*data)->player->pos = (t_p){MIN_WIDTH / 2, MIN_HEIGHT / 2};
	(*data)->wall_mov = (t_p){0, 0};
	(*data)->p_index = find_plyr((*data));
	(*data)->offs.x = (*data)->player->pos.x - TILE_S * (*data)->p_index.x;
	(*data)->offs.y = (*data)->player->pos.y - TILE_S * (*data)->p_index.y;
	(*data)->plyr_cntr.x = MIN_WIDTH / 2 + TILE_S / 2;
	(*data)->plyr_cntr.y = MIN_HEIGHT / 2 + TILE_S / 2;
	return (0);
}
