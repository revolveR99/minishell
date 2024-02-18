/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conver_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:40:40 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 01:06:55 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*int_to_str(long l)
{
	size_t	i;
	int		sign;
	char	*res;
	long	tmp;

	sign = 1;
	if (l < 0)
		sign = -1;
	tmp = (long) l * sign;
	i = len_of_int(tmp, sign);
	res = (char *) malloc(i + 1);
	if (!res)
		return (NULL);
	res[i--] = '\0';
	while (tmp > 9)
	{
		res[i] = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	res[i] = (char)(tmp % 10) + '0';
	if (sign == -1)
		res[0] = '-';
	return (res);
}

size_t	len_of_int(long l, int sign)
{
	size_t	i;

	i = 1;
	while (l > 9)
	{
		l /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return ((long) sign * result);
}
