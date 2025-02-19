/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:49:56 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 17:17:11 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	while ((s1[i] || s2[i]) && ((s1[i] == s2[i]) && (s1[i] || s2[i])))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(src);
	if (i + 1 < dstsize)
	{
		ft_memcpy(dst, src, i + 1);
	}
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (ss1[i] && ss2[i] && (i < n - 1) && ss1[i] == ss2[i])
		i++;
	return (ss1[i] - ss2[i]);
}
