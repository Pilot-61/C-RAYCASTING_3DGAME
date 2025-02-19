/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_helpers3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:01:04 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 18:27:50 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}

static int	init_first_map_line(char *line, t_data *game)
{
	game->md.temp_map = gcollector(sizeof(char *), 1);
	if (!game->md.temp_map)
		return (1);
	game->md.temp_map[0] = ft_strdup(line);
	if (!game->md.temp_map[0])
		return (1);
	game->md.height = 1;
	game->md.width = ft_strlen(line);
	return (0);
}

static int	copy_existing_map(char **temp_map, t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->md.height)
	{
		temp_map[i] = ft_strdup(game->md.temp_map[i]);
		if (!temp_map[i])
			return (1);
	}
	return (0);
}

static int	add_new_line(char **temp_map, char *line, int i)
{
	temp_map[i] = ft_strdup(line);
	if (!temp_map[i])
		return (1);
	return (0);
}

int	parse_map_line(char *line, t_data *game, int *nl)
{
	char	**temp_map;

	if (line[0] == '\n')
		*nl = 1;
	remove_newline(line);
	if (!game->md.height)
		return (init_first_map_line(line, game));
	temp_map = gcollector(sizeof(char *) * (game->md.height + 1), 1);
	if (!temp_map)
		return (1);
	if (copy_existing_map(temp_map, game))
		return (1);
	if (add_new_line(temp_map, line, game->md.height))
		return (1);
	game->md.temp_map = temp_map;
	game->md.height++;
	if (ft_strlen(line) > (size_t)game->md.width)
		game->md.width = ft_strlen(line);
	return (0);
}
