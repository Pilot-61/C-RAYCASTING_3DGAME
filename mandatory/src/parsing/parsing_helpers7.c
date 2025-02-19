/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:14:24 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 15:14:26 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	flood_fill(char **map, int x, int y, int *invalid)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == ' ' || map[y][x] == '-')
	{
		*invalid = 1;
		return ;
	}
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, invalid);
	flood_fill(map, x - 1, y, invalid);
	flood_fill(map, x, y + 1, invalid);
	flood_fill(map, x, y - 1, invalid);
}

void	get_pos(char **map, int height, int width, t_player_pos *pos)
{
	int	x;
	int	y;

	y = 0;
	pos->x = -1;
	pos->y = -1;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				pos->x = x;
				pos->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	valid_bound(t_data *game)
{
	char			**validation_map;
	int				invalid;
	t_player_pos	pos;
	int				max_width;

	validation_map = valid_map(game);
	if (!validation_map)
		return (1);
	invalid = 0;
	max_width = get_max_width(game->md.temp_map, game->md.height);
	get_pos(validation_map, game->md.height, max_width, &pos);
	if (pos.x != -1)
		flood_fill(validation_map, pos.x, pos.y, &invalid);
	return (invalid);
}

static void	fill_map_line(char *dest, char *src, int width)
{
	int	j;

	j = 0;
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	while (j < width)
	{
		dest[j] = '1';
		j++;
	}
	dest[j] = '\0';
}

char	**duplicate_map(char **src, int height, int width)
{
	int		i;
	char	**temp_map;

	temp_map = gcollector(sizeof(char *) * (height + 1), 1);
	if (!temp_map)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		temp_map[i] = gcollector(sizeof(char) * (width + 1), 1);
		if (!temp_map[i])
			return (NULL);
		fill_map_line(temp_map[i], src[i], width);
	}
	temp_map[i] = NULL;
	return (temp_map);
}
