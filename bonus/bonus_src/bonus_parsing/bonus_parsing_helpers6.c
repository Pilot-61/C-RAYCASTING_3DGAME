/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_helpers6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:32:54 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 17:33:09 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	is_sep(char c)
{
	return (c == ' ' || c == '1' || c == '\n');
}

int	map_bordered(char **map, int height)
{
	int		j;
	char	*line;

	j = -1;
	while (map[0][++j])
	{
		if (!is_sep(map[0][j]))
			return (1);
	}
	j = -1;
	while (map[height - 1][++j])
	{
		if (!is_sep(map[height - 1][j]))
			return (1);
	}
	j = 1;
	while (map[j] && j < height - 1)
	{
		line = ft_strtrim(map[j], " ");
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	is_empty_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\0')
			return (0);
		j++;
	}
	return (1);
}
