/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:01:09 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/11 14:33:17 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	validate_file_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strcmp(filename + len - 4, ".cub"));
}

int	tex_id(char *line)
{
	return (!ft_strncmp(line, "NO ", 2) || !ft_strncmp(line, "SO ", 2)
		|| !ft_strncmp(line, "WE ", 2) || !ft_strncmp(line, "EA ", 2));
}

char	*get_texture_path(char *line)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (NULL);
	path = ft_strdup(&line[i]);
	if (path && path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

int	handle_texture(t_textures *tex, char *path, char *id, char **t_field)
{
	if (*t_field)
	{
		printf("Error\nDuplicate texture id: %s\n", id);
		return (1);
	}
	*t_field = path;
	tex->count++;
	return (0);
}

int	s_tex(t_textures *tex, char *line)
{
	char	*path;

	path = get_texture_path(line);
	path = ft_strtrim(path, " ");
	if (!path)
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
		return (handle_texture(tex, path, "NO", &tex->no));
	else if (!ft_strncmp(line, "SO ", 3))
		return (handle_texture(tex, path, "SO", &tex->so));
	else if (!ft_strncmp(line, "WE ", 3))
		return (handle_texture(tex, path, "WE", &tex->we));
	else if (!ft_strncmp(line, "EA ", 3))
		return (handle_texture(tex, path, "EA", &tex->ea));
	else
	{
		printf("Error\nInvalid texture identifier\n");
		return (1);
	}
}
