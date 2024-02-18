/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:46 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/15 10:30:26 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swapping(t_envp **first, t_envp *swap_a)
{
	t_envp	*temp;
	t_envp	*swap_b;

	if (!first || !swap_a)
		return ;
	temp = *first;
	while (temp && temp != swap_a && temp->next != swap_a)
		temp = temp->next;
	swap_b = swap_a->next;
	swap_a->next = swap_b->next;
	swap_b->next = swap_a;
	if (*first == swap_a)
	{
		*first = swap_b;
	}
	else
		temp->next = swap_b;
}

void	quote_adding(t_envp *envp)
{
	t_envp	*temp;
	char	*new_value;
	int		len;

	temp = envp;
	while (temp)
	{
		len = (ft_pos_in_string(temp->var, '='));
		if (len == (int) ft_strlen(temp->var))
			len = 0;
		if (len > 0)
		{
			new_value = (char *) malloc(ft_strlen(temp->var) + 3);
			len++;
			strn_cpy(new_value, temp->var, len + 1);
			strn_cpy(&new_value[len], "\"", 0);
			strn_cpy(&new_value[len + 1], &temp->var[len], 0);
			len = ft_strlen(new_value);
			strn_cpy(&new_value[len], "\"", 0);
			free((void *) temp->var);
			temp->var = new_value;
		}
		temp = temp->next;
	}
}

t_envp	*env_list_clonning(t_envp *envp)
{
	t_envp	*output;
	t_envp	*temp;

	output = (lst_new(envp->var));
	temp = envp->next;
	while (temp)
	{
		add_back_list(&output, lst_new(temp->var));
		temp = temp->next;
	}
	return (output);
}
