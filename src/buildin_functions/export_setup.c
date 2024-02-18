/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:36 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:13:50 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_export(t_data *data, t_comd *comd)
{
	t_envp	*temp;

	if (!comd->argv)
		variable_printing(data);
	temp = comd->argv;
	while (temp)
	{
		if (!validity_check(temp->var))
		{
			ft_error_printer(comd, ERROR_NOT_VALID, temp->var);
		}
		else if (comd == data->c_line)
			update_env(data, temp->var);
		temp = temp->next;
	}
	return (RETURN_SUCCESSFUL);
}

void	update_env(t_data *data, char *var)
{
	t_envp	*temp;

	temp = retrieve_env_element(data->envp, var);
	if (temp)
	{
		free((void *) temp->var);
		temp->var = ft_strndup(var);
	}
	else
		add_back_list(&data->envp, lst_new(var));
}

int	validity_check(char *argv)
{
	int	i;

	i = 0;
	if ((argv[0] >= '0' && argv[0] <= '9') || argv[0] == '=')
		return (0);
	while (argv[i] && argv[i] != '=')
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9')
			&& argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	variable_printing(t_data *data)
{
	t_envp	*temp;
	t_envp	*copy;

	copy = env_list_clonning(data->envp);
	quote_adding(copy);
	list_sorting(&copy);
	temp = copy;
	while (temp)
	{
		ft_write_fd(data->c_line->fd->out, EXPORT);
		ft_write_fd_nl(data->c_line->fd->out, temp->var);
		temp = temp->next;
	}
	delete_list(&copy);
}

void	list_sorting(t_envp **envp)
{
	t_envp	*temp;
	int		sorted;
	int		equation;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		temp = *envp;
		while (temp && temp->next)
		{
			equation = ft_strncmp(temp->var, temp->next->var,
					ft_pos_in_string(temp->var, '='));
			if (equation > 0)
			{
				swapping(envp, temp);
				sorted = 0;
			}
			else
				temp = temp->next;
		}
	}
}
