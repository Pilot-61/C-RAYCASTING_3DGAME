/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilot <pilot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:50:02 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/19 11:38:37 by pilot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

bool	ft_is_whitespace(char c)
{
	return (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	handle_overflow(int sign, int int_max, int int_min)
{
	if (sign == 1)
		return (int_max);
	else
		return (int_min);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	ft_atoi2(char *str)
{
	int	i;
	int	sign;
	int	res;
	int	int_max;
	int	int_min;

	(1) && (i = 0, sign = 1, res = 0, int_max = 2147483647,
		int_min = -2147483648, 0);
	skip_spaces(str, &i);
	if (ft_is_whitespace(str[i]))
		return (-1);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_is_digit(str[i]))
	{
		if (res > int_max / 10 || (res == int_max / 10 && str[i] - '0' > 7))
			return (handle_overflow(sign, int_max, int_min));
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
