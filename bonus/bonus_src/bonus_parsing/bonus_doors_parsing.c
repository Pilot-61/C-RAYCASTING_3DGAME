/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_doors_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:45:55 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/16 19:58:51 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

int	count_doors(t_data *data)
{
	int	i;
	int	j;
	int	count;
	int	max_width;

	count = 0;
	i = 0;
	while (i < data->md.height)
	{
		max_width = ft_strlen(data->md.temp_map[i]);
		j = 0;
		while (j < max_width)
		{
			if (data->md.temp_map[i][j] == 'D')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	setup_door(t_data *data, int door_index, int i, int j)
{
	data->t_doors[door_index] = gcollector(sizeof(t_doors), 1);
	data->t_doors[door_index]->pos.x = j;
	data->t_doors[door_index]->pos.y = i;
	data->t_doors[door_index]->state = false;
	data->t_doors[door_index]->id = door_index;
}

void	init_doors(t_data *data)
{
	int	door_count;
	int	i;
	int	j;
	int	door_index;
	int	max_width;

	door_count = count_doors(data);
	if (door_count == 0)
	{
		data->t_doors = gcollector(sizeof(t_doors *), 1);
		data->t_doors[0] = NULL;
		return ;
	}
	data->t_doors = gcollector(sizeof(t_doors *) * (door_count + 1), 1);
	data->t_doors[door_count] = NULL;
	door_index = 0;
	i = -1;
	while (++i < data->md.height && door_index < door_count)
	{
		max_width = ft_strlen(data->md.temp_map[i]);
		j = -1;
		while (++j < max_width && door_index < door_count)
			if (data->md.temp_map[i][j] == 'D')
				setup_door(data, door_index++, i, j);
	}
}

static int	check_door_position(t_data *data, int i, int j, int height)
{
	int	width;
	int	horizontal_wall_only;
	int	vertical_wall_only;

	width = ft_strlen(data->md.temp_map[i]);
	horizontal_wall_only = ((j > 0 && j < width - 1)
			&& (data->md.temp_map[i][j - 1] == '1'
				&& data->md.temp_map[i][j + 1] == '1')
			&& (data->md.temp_map[i - 1][j] == '0'
				&& data->md.temp_map[i + 1][j] == '0'));
	vertical_wall_only = ((i > 0 && i < height - 1)
			&& (data->md.temp_map[i - 1][j] == '1'
				&& data->md.temp_map[i + 1][j] == '1')
			&& (data->md.temp_map[i][j - 1] == '0'
				&& data->md.temp_map[i][j + 1] == '0'));
	if (!(horizontal_wall_only || vertical_wall_only))
	{
		printf("Error: Door at position (%d, %d) not properly surrounded\n",
			i, j);
		return (1);
	}
	return (0);
}

int	pars_surrounded_doors(t_data *data)
{
	int	i;
	int	j;
	int	height;
	int	width;

	height = data->md.height;
	i = -1;
	while (++i < height)
	{
		width = ft_strlen(data->md.temp_map[i]);
		j = -1;
		while (++j < width)
			if (data->md.temp_map[i][j] == 'D')
				if (check_door_position(data, i, j, height))
					return (1);
	}
	return (0);
}
