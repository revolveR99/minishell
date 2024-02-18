/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mem_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:40:54 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 03:29:35 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		value;
	size_t				i;

	if (n > 0)
	{
		i = 0;
		ptr = (unsigned char *) str;
		value = (unsigned char) c;
		while (i < n)
		{
			*ptr = value;
			ptr++;
			i++;
		}
	}
	return (str);
}

size_t	strn_cpy(char *dest, char *sourc, size_t n)
{
	size_t	i;

	i = 0;
	if (sourc && n == 0)
	{
		while (sourc[i])
		{
			dest[i] = sourc[i];
			i++;
		}
	}
	else if (sourc)
	{
		n--;
		while (i < n && sourc[i])
		{
			dest[i] = sourc[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (i);
}

char	*ft_strndup(const char *str)
{
	char	*res;

	res = (char *) malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	strn_cpy(res, (char *)str, 0);
	return (res);
}

char	*retrieve_substr(char const *str, size_t start, size_t len)
{
	char	*substr;

	if (!str)
		return (NULL);
	substr = (char *) malloc(len + 1);
	if (!substr)
		return (NULL);
	strn_cpy(substr, (char *) &str[start], len + 1);
	return (substr);
}
