/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:50:11 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 17:17:05 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		start = slen;
	if (len > slen - start)
		len = slen - start;
	sub = gcollector(len + 1, 1);
	if (!sub)
		return (NULL);
	while (start < slen && len > i)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = gcollector(ft_strlen(s1) + 1, 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	if ((int)count < 0 || (int)size < 0)
		return (NULL);
	i = count * size;
	ptr = gcollector(i, 1);
	if (ptr == NULL)
		return (NULL);
	while (i > 0)
	{
		*ptr = 0;
		ptr++;
		i--;
	}
	return ((void *)(ptr - count * size));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens;
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lens = ft_strlen(s1) + ft_strlen(s2);
	str = gcollector(lens + 1, 1);
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
