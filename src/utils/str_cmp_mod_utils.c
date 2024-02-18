/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cmp_mod_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:41:12 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 03:40:05 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pos_in_string(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_remove_char(char *str, char c)
{
	char	*output;
	char	*temp;
	int		i;
	int		count;

	count = count_of_char_instr(str, c);
	if (count == 0)
		return (str);
	temp = str;
	output = (char *) malloc((ft_strlen(str) - count) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			output[i] = *str;
			i++;
		}
		str++;
	}
	output[i] = '\0';
	free((void *) temp);
	return (output);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

size_t	ft_replace_in_string(char *str, char c_replace, char c_with)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == c_replace)
		{
			*str = c_with;
			count++;
		}
		str++;
	}
	return (count);
}
