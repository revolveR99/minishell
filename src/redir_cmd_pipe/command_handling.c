/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:53 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:19:52 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_comd	*new_commd_element(void)
{
	t_comd	*output;

	output = (t_comd *) malloc(sizeof(t_comd));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_comd));
	output->fd = (t_fd *) malloc(sizeof(t_fd));
	if (!output->fd)
		return (NULL);
	output->fd->in = STDIN_FILENO;
	output->fd->out = STDOUT_FILENO;
	output->fd->err = STDERR_FILENO;
	output->result = RETURN_FALSE;
	output->re = NULL;
	return (output);
}

void	cleanup_command(t_comd **commands)
{
	t_comd	*temp;

	while (*commands)
	{
		temp = *commands;
		*commands = (*commands)->next;
		free((void *) temp->comd);
		free((void *) temp->fd);
		temp->fd = NULL;
		temp->comd = NULL;
		delete_list(&temp->argv);
		delete_redir_list(&temp->re);
		free((void *) temp);
		temp = NULL;
	}
}

int	run_builtin_comd(t_comd *comd, t_data *data)
{
	if (ft_strcmp(comd->comd, "exit"))
		return (handle_exit_comd(comd, data));
	else if (ft_strcmp(comd->comd, "pwd"))
		return (get_current_path(data, comd));
	else if (ft_strcmp(comd->comd, "env"))
		return (base_env(data, comd));
	else if (ft_strcmp(comd->comd, "export"))
		return (handle_export(data, comd));
	else if (ft_strcmp(comd->comd, "unset"))
		return (unset_env_variable(data, comd));
	else if (ft_strcmp(comd->comd, "cd"))
		return (change_directory(data, comd));
	else if (ft_strcmp(comd->comd, "echo"))
		return (handle_echo(comd));
	else if (ft_strcmp(comd->comd, "error_codes"))
		return (err_code(comd));
	return (RETURN_FALSE);
}

void	display_comds(t_comd *commands)
{
	t_envp	*temp;
	int		i;

	while (commands)
	{
		i = 0;
		temp = commands->argv;
		while (temp)
		{
			printf("argc=%i [%s]\n", i, temp->var);
			temp = temp->next;
			i++;
		}
		if (commands)
			commands = commands->next;
	}
}
