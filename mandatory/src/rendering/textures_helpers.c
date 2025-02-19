/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:14:16 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 15:14:19 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

mlx_texture_t	*get_wall_texture(t_data *data, int i)
{
	if (data->d_rays[i].direction == 'N')
		return (data->textures->no_texture);
	else if (data->d_rays[i].direction == 'S')
		return (data->textures->so_texture);
	else if (data->d_rays[i].direction == 'E')
		return (data->textures->ea_texture);
	else if (data->d_rays[i].direction == 'W')
		return (data->textures->we_texture);
	return (NULL);
}
