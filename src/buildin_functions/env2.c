/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:20 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/14 12:42:32 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*retrive_env(char *var, t_envp *envp_list)
{
	while (!cmpare_varable(var, envp_list->var))
	{
		envp_list = envp_list->next;
		if (envp_list == NULL)
			return (NULL);
	}
	return (&envp_list->var[ft_pos_in_string(envp_list->var, '=') + 1]);
}
