/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:40:32 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 04:10:34 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_bits(int input)
{
	int		i;
	char	c;

	i = 31;
	while (i >= 0)
	{
		c = (((input >> i) & 1) + '0');
		write(1, &c, 1);
		i--;
	}
	write(1, "\n", 1);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free((void *) ptr);
	ptr = NULL;
}

void	free_chr_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
	{
		free((void *) array[i]);
		array[i] = NULL;
		i++;
	}
	free((void *) array);
	array = NULL;
}

char	*mem_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	ssize_t		s1_len;
	char		*res;

	s1_len = ft_strlen(s1);
	res = (char *) malloc(s1_len + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	strn_cpy(res, s1, 0);
	strn_cpy(&res[s1_len], s2, 0);
	if (free_s1)
		free((void *) s1);
	if (free_s2)
		free((void *) s2);
	return (res);
}
