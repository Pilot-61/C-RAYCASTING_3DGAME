/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_helpers5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:32:14 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 14:46:17 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	parse_color(char *line, int *r, int *g, int *b)
{
	char	**colors;
	int		i;

	line += 2;
	while (line && (*line == ' '))
		line++;
	if (count_commas(line) != 2)
		return (1);
	colors = ft_split(line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		return (1);
	i = 0;
	while (i < 3)
	{
		if (check_color_format(colors[i]))
			return (1);
		i++;
	}
	*r = ft_atoi2(colors[0]);
	*g = ft_atoi2(colors[1]);
	*b = ft_atoi2(colors[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (1);
	return (0);
}

int	process_color(t_colors *colors, char *line,
		int *floor_set, int *ceiling_set)
{
	if (is_color_id(line))
	{
		if (*line == 'F' && !*floor_set)
		{
			if (parse_color(line, &colors->f_red,
					&colors->f_green, &colors->f_blue))
				return (1);
			colors->c_floor = get_rgba(colors->f_red,
					colors->f_green, colors->f_blue, 255);
			*floor_set = 1;
		}
		else if (*line == 'C' && !*ceiling_set)
		{
			if (parse_color(line, &colors->c_red,
					&colors->c_green, &colors->c_blue))
				return (1);
			colors->c_ceiling = get_rgba(colors->c_red, colors->c_green,
					colors->c_blue, 255);
			*ceiling_set = 1;
		}
		else
			return (1);
	}
	return (0);
}
