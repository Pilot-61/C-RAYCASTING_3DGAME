/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parsing_helpers2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:01:07 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 14:51:59 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	is_color_id(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	count_commas(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	check_color_format(char *color)
{
	int	i;

	i = 0;
	while (color[i] && (color[i] == ' '))
		i++;
	if (!color[i] || !ft_isdigit(color[i]))
		return (1);
	while (color[i] && ft_isdigit(color[i]))
		i++;
	while (color[i])
	{
		if (color[i] != ' ' && color[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
