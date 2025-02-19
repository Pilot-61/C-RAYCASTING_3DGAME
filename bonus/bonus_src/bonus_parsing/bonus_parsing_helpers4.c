/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_helpers4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:01:00 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 18:27:50 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	get_max_width(char **map, int height)
{
	size_t	max_width;
	int		i;
	size_t	len;

	max_width = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

int	square_map(char **normalized, char **original,
	int height, size_t max_width)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < height)
	{
		normalized[i] = gcollector(sizeof(char) * (max_width + 1), 1);
		if (!normalized[i])
			return (1);
		j = -1;
		while (++j < max_width)
		{
			if (j < ft_strlen(original[i]))
			{
				if (original[i][j] == 32)
					normalized[i][j] = '1';
				else
					normalized[i][j] = original[i][j];
			}
			else
				normalized[i][j] = '1';
		}
		normalized[i][j] = '\0';
	}
	return (normalized[i] = NULL, 0);
}

int	normalize_map(char **normalized, char **original,
	int height, size_t max_width)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		normalized[i] = gcollector(sizeof(char) * (max_width + 1), 1);
		if (!normalized[i])
			return (1);
		j = 0;
		while (j < max_width)
		{
			if (j < ft_strlen(original[i]))
				normalized[i][j] = original[i][j];
			else
				normalized[i][j] = '-';
			j++;
		}
		normalized[i][j] = '\0';
		i++;
	}
	normalized[i] = NULL;
	return (0);
}

int	check_map_content(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != ' ' && map[i][j] != 'D')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**valid_map(t_data *game)
{
	char	**normalized;
	int		max_width;
	char	**temp_map;

	max_width = get_max_width(game->md.temp_map,
			game->md.height);
	normalized = gcollector(sizeof(char *) * (game->md.height + 1), 1);
	temp_map = gcollector(sizeof(char *) * (game->md.height + 1), 1);
	if (!normalized || !temp_map)
		return (NULL);
	if (check_map_content(game->md.temp_map, game->md.height))
		return (NULL);
	if (normalize_map(normalized, game->md.temp_map,
			game->md.height, max_width))
		return (NULL);
	if (square_map(temp_map, game->md.temp_map,
			game->md.height, max_width))
		return (NULL);
	game->md.normalized_map = duplicate_map(temp_map,
			game->md.height, max_width);
	return (normalized);
}
