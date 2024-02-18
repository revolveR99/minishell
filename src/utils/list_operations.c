/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:06 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:13:50 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp	*env_clone(char **envp)
{
	t_envp	*output;
	int		i;

	output = lst_new(envp[0]);
	i = 1;
	while (envp[i])
	{
		add_back_list(&output, lst_new(envp[i]));
		i++;
	}
	return (output);
}

t_envp	*lst_new(char *content)
{
	t_envp	*new_element;

	new_element = (t_envp *) malloc(sizeof(t_envp));
	if (!new_element)
		return (NULL);
	new_element->var = ft_strndup(content);
	new_element->next = NULL;
	return (new_element);
}

t_envp	*last_lst(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back_list(t_envp **lst, t_envp *new)
{
	if (!*lst)
		*lst = new;
	else
		last_lst(*lst)->next = new;
}

void	delete_list(t_envp **lst)
{
	t_envp	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free((void *) temp->var);
		free((void *) temp);
	}
	*lst = NULL;
}
