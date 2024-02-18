/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:45:07 by kryxaurus         #+#    #+#             */
/*   Updated: 2024/01/17 01:12:18 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_shell(t_data *data)
{
	data->r_line = NULL;
	ft_clear_memory(data);
	exit(data->errnum);
}

void	handle_readline(t_data *data)
{
	data->r_line = readline(PROMPT);
	if (data->r_line == NULL)
	{
		data->r_line = NULL;
	}
	else
	{
		if (ft_strlen(data->r_line) > 0)
			add_history(data->r_line);
	}
}

t_return	handle_commands(t_data *data)
{
	if (data->r_line)
	{
		ft_parse_shell_input(data);
		if (ft_process_all_command_redirections(data) == RETURN_SUCCESSFUL)
		{
			if (ft_cycle_commands(data) == RETURN_EXIT)
			{
				free(data->r_line);
				return (RETURN_EXIT);
			}
		}
	}
	return (RETURN_SUCCESSFUL);
}

void	cleanup_after_execution(t_data *data)
{
	if (data->r_line)
	{
		ft_wait_for_children(data);
		free((void *)data->r_line);
		data->r_line = NULL;
		cleanup_command(&data->c_line);
	}
}
