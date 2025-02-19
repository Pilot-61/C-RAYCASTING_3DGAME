/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:49:49 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/12 17:17:16 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

static int	mes_len(const char *s, char c)
{
	int	existe;
	int	counter;

	existe = 0;
	counter = 0;
	while (*s != '\0')
	{
		if (*s != c && existe == 0)
		{
			existe = 1;
			counter++;
		}
		else if (*s == c)
		{
			existe = 0;
		}
		s++;
	}
	return (counter);
}

static char	*mes_findndcpy(char const *s, char c, int i)
{
	int		j;
	char	*str;
	int		len;

	j = 0;
	len = 0;
	while (s[i + len] != c && s[i + len])
		len++;
	str = gcollector((len + 1) * sizeof(char), 1);
	if (!str)
		return (NULL);
	while (s[i] != c && s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	**mes_allocat(char const *s, char c, char **array, int wordscount)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < wordscount)
	{
		while (s[i] == c && s[i])
			i++;
		array[j] = mes_findndcpy(s, c, i);
		if (!array[j])
			return (NULL);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	array[wordscount] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		wordscount;

	if (!s)
		return (NULL);
	wordscount = mes_len(s, c);
	array = gcollector((wordscount + 1) * sizeof(char *), 1);
	if (!array)
		return (NULL);
	return (mes_allocat(s, c, array, wordscount));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*m;
	unsigned char	*a;
	size_t			i;

	if (src == NULL && dst == NULL)
		return (dst);
	m = (unsigned char *)dst;
	a = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(m++) = *(a++);
		i++;
	}
	return (dst);
}
