/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:14:57 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 21:52:39 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	init_parse_vars(t_data *data)
{
	data->vars.floor_set = 0;
	data->vars.ceiling_set = 0;
	data->vars.map_set = 0;
	data->vars.is_newline = 0;
	data->vars.tr = 0;
}

static int	handle_map_line(t_data *data)
{
	if (data->vars.is_newline)
		return (1);
	if (parse_map_line(data->vars.line, data, &data->vars.is_newline))
		return (1);
	data->vars.map_set = 1;
	return (0);
}

static int	check_map_validity(t_data *data)
{
	if (data->vars.map_set && map_bordered(data->md.temp_map, data->md.height))
	{
		printf("Error: Map is not surrounded by walls\n");
		return (1);
	}
	if (data->vars.tr && check_map_newlines(data->md.temp_map, data->md.height))
		return (1);
	return (0);
}

int	check_line(t_data *data)
{
	if (data->vars.map_set == 1 && !is_map_line(data->vars.line)
		&& !is_empty_line(data->vars.line))
		data->vars.tr = 1;
	if ((tex_id(data->vars.line) && s_tex(data->textures, data->vars.line))
		|| data->vars.tr == 1)
		return (1);
	else if ((process_color(data->colors, data->vars.line,
				&data->vars.floor_set, &data->vars.ceiling_set))
		|| data->vars.tr == 1)
		return (1);
	else if (is_map_line(data->vars.line) && handle_map_line(data))
		return (1);
	return (0);
}

int	parse_file(int fd, t_data *data)
{
	int		ret;

	ret = 0;
	(1) && (init_parse_vars(data), data->vars.line = get_next_line(fd), 0);
	while (data->vars.line)
	{
		if (check_line(data))
			return (1);
		else if (data->vars.line[0] != '\n' && !is_map_line(data->vars.line))
			ret++;
		data->vars.line = get_next_line(fd);
	}
	if (check_map_validity(data) || ret > 6)
		return (1);
	init_player_pos(data);
	if (valid_bound(data) || data->md.player_count > 1
		|| data->md.player_count == 0)
		return (1);
	return (!(data->textures->count == 4
			&& data->vars.floor_set && data->vars.ceiling_set));
}
