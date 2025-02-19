/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:28:51 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 15:13:37 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_get_the_next(char *result)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i])
	{
		return (NULL);
	}
	line = ft_calloc((ft_strlen(result) - i + 1), 1);
	i++;
	while (result[i])
		line[j++] = result[i++];
	return (line);
}

char	*ft_get_the_line(char *result)
{
	char	*getline;
	int		i;

	i = 0;
	if (!result[i])
		return (NULL);
	while (result[i] && result[i] != '\n')
		i++;
	if (result[i] == '\n')
		getline = ft_calloc (i + 2, 1);
	else
		getline = ft_calloc (i + 1, 1);
	i = 0;
	while (result[i] && result[i] != '\n')
	{
		getline[i] = result[i];
		i++;
	}
	if (result[i] && result[i] == '\n')
		getline[i++] = '\n';
	return (getline);
}

char	*ft_read_line(int fd, char *result)
{
	char	*buffer;
	int		i;

	buffer = ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			return (NULL);
		}
		buffer[i] = 0;
		result = ft_strjoin(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		return (NULL);
	}
	result = ft_read_line(fd, result);
	if (!result)
		return (NULL);
	line = ft_get_the_line(result);
	result = ft_get_the_next(result);
	return (line);
}
