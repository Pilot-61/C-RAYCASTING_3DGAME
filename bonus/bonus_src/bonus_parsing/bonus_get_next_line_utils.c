/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:41:54 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 22:12:36 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_map_newlines(char **map, int height)
{
	int	map_started;
	int	i;

	map_started = 0;
	i = 0;
	while (i < height)
	{
		if (!map_started && map[i][0] != '\0' && map[i][0] != '\n')
			map_started = 1;
		if (map_started && is_empty_line(map[i]))
			return (1);
		i++;
	}
	return (0);
}

void	init_player_pos(t_data *game)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < game->md.height)
	{
		j = -1;
		while (++j < ft_strlen(game->md.temp_map[i]))
		{
			if (game->md.temp_map[i][j] == 'N' || game->md.temp_map[i][j] == 'S'
			|| game->md.temp_map[i][j] == 'E' || game->md.temp_map[i][j] == 'W')
			{
				game->md.player_count++;
				game->md.player_dir = game->md.temp_map[i][j];
				if (game->md.temp_map[i][j] == 'N')
					game->player->rotate_angle = 3 * M_PI / 2;
				else if (game->md.temp_map[i][j] == 'S')
					game->player->rotate_angle = M_PI / 2;
				else if (game->md.temp_map[i][j] == 'E')
					game->player->rotate_angle = 0;
				else if (game->md.temp_map[i][j] == 'W')
					game->player->rotate_angle = M_PI;
			}
		}
	}
}

int	is_map_line(char *line)
{
	while (*line && (*line == ' '))
		line++;
	if (line[0] == '0' || line[0] == '1')
		return (1);
	return (0);
}
