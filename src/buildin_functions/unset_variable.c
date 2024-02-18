/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:53:03 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/14 21:20:59 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset_env_variable(t_data *data, t_comd *comd)
{
	t_envp	*temp;
	t_envp	*argv_temp;

	argv_temp = comd->argv;
	while (argv_temp)
	{
		if (!validity_check(argv_temp->var))
		{
			ft_error_printer(comd, ERROR_NOT_VALID, argv_temp->var);
		}
		else if (comd == data->c_line)
		{
			temp = retrieve_env_element(data->envp, argv_temp->var);
			if (temp)
				erase_envr_element(&data->envp, temp);
		}
		argv_temp = argv_temp->next;
	}
	return (RETURN_SUCCESSFUL);
}

void	erase_envr_element(t_envp **first, t_envp *to_del)
{
	t_envp	*temp;

	if (!first || !to_del)
		return ;
	temp = *first;
	while (temp && temp != to_del && temp->next != to_del)
		temp = temp->next;
	free((void *) to_del->var);
	if (*first == to_del)
		*first = to_del->next;
	else
		temp->next = to_del->next;
	free((void *) to_del);
}
