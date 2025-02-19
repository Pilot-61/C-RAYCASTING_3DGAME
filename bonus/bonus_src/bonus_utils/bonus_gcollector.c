/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_gcollector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:41:53 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/14 14:47:59 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

void	clear_gc(t_gc **gc)
{
	t_gc	*tmp;
	t_gc	*node;

	tmp = *gc;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		free(node->content);
		free(node);
	}
	gc = NULL;
}

void	*gcollector(size_t size, int mode)
{
	static t_gc	*gc;
	t_gc		*node;
	void		*data;

	if (mode)
	{
		data = malloc(size);
		if (!data)
			return (clear_gc(&gc), exit(1), NULL);
		node = malloc(sizeof(t_gc));
		if (!node)
			return (clear_gc(&gc), free(data), NULL);
		node->content = data;
		node->next = gc;
		gc = node;
		return (data);
	}
	else
		return (clear_gc(&gc), NULL);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*i;

	i = (unsigned char *)b;
	while (len-- > 0)
	{
		*i++ = c;
	}
	return (b);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	char	*new;

	new = (char *)s1;
	if (!s1 || !set)
		return (0);
	while (*s1 != '\0' && ft_strchr(set,*s1) != 0)
		s1++;
	len = ft_strlen(s1);
	if (len != 0)
		while (len >= 0 && ft_strchr(set, s1[len]) != 0)
			len--;
	new = ft_substr((char *)s1, 0, len + 1);
	return (new);
}
