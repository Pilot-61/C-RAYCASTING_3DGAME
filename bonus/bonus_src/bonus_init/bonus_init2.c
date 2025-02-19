/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzahri <hzahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:20 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/13 16:12:49 by hzahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

char	*ft_itoa(int i)
{
	char	*str;
	int		len;
	int		tmp;

	len = 1;
	tmp = i;
	tmp /= 10;
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	str = gcollector(sizeof(char) * (len + 1), 1);
	str[len] = '\0';
	while (len--)
	{
		str[len] = i % 10 + '0';
		i /= 10;
	}
	return (str);
}

int	load_sprites(t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	while (i < 340)
	{
		if (i == 0)
			data->sprite.is_first = true;
		path = ft_strjoin("images/sprites/", ft_itoa(i + 1));
		data->sprite.texture_path[i] = ft_strjoin(path, ".png");
		data->sprite.texture[i] = mlx_load_png(data->sprite.texture_path[i]);
		if (!data->sprite.texture[i])
			error();
		i++;
	}
	return (0);
}

void	print_loading_ascii(void)
{
	int		i;
	char	*loading_text[8];

	loading_text[0]
		= "                                                                ";
	loading_text[1]
		= "██╗      ██████╗  █████╗ ██████╗ ██╗███╗   ██╗ ██████╗          ";
	loading_text[2]
		= "██║     ██╔═══██╗██╔══██╗██╔══██╗██║████╗  ██║██╔════╝          ";
	loading_text[3]
		= "██║     ██║   ██║███████║██║  ██║██║██╔██╗ ██║██║  ███╗         ";
	loading_text[4]
		= "██║     ██║   ██║██╔══██║██║  ██║██║██║╚██╗██║██║   ██║         ";
	loading_text[5]
		= "███████╗╚██████╔╝██║  ██║██████╔╝██║██║ ╚████║╚██████╔╝██╗██╗██╗";
	loading_text[6]
		= "╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝╚═╝";
	loading_text[7] = NULL;
	i = 0;
	while (loading_text[i])
	{
		printf("%s\n", loading_text[i]);
		i++;
	}
}
