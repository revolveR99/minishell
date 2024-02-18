/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 03:51:51 by kryxaurus         #+#    #+#             */
/*   Updated: 2024/01/16 04:05:27 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	char	*ptr;

	i = 0;
	little_len = ft_strlen(little);
	ptr = (char *) big;
	if (little_len == 0)
		return (ptr);
	if (little_len > ft_strlen(big))
		return (NULL);
	while (i + little_len <= len)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(&big[i], little, little_len) == 0)
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}

size_t	str_word_count(char const *str, const char c)
{
	size_t	word_count;

	word_count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			while (*str && *str != c)
				str++;
			word_count++;
		}
	}
	return (word_count);
}

size_t	count_of_char_instr(const char *str, const char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*find_char_in_str(const char *str, const char c)
{
	char	*tmp;

	if (!str || !c)
		return (NULL);
	tmp = (char *) str;
	while (*tmp)
	{
		if (*tmp == c)
			return ((char *)tmp);
		tmp++;
	}
	return (NULL);
}
