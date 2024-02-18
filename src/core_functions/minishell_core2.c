/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_core2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 03:54:48 by kryxaurus         #+#    #+#             */
/*   Updated: 2024/01/17 15:10:43 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_clear_memory(t_data *data)
{
	t_comd	*temp;

	delete_list(&data->envp);
	if (data->c_line)
	{
		temp = last_command(data->c_line);
		data->errnum = temp->errnum;
		cleanup_command(&data->c_line);
	}
	rl_clear_history();
	free(data->pwd);
	if (data->r_line)
		ft_write_fd(STDOUT_FILENO, "exit\n");
}

void	ft_wait_for_children(t_data *data)
{
	t_comd		*temp;
	int			status;

	if (!data->c_line)
		return ;
	temp = data->c_line;
	status = 0;
	while (temp)
	{
		if (temp->pid != 0 && waitpid(temp->pid, &status, 0) != RETURN_ERR)
		{
			if (WIFEXITED(status))
				temp->errnum = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				temp->errnum = 128 + WTERMSIG(status);
		}
		temp = temp->next;
	}
	temp = last_command(data->c_line);
	data->errnum = temp->errnum;
	setup_interactive_parent();
}

void	ft_init(t_data *data, char **envp)
{
	char	*output;
	t_envp	*temp_envp;

	data->c_line = NULL;
	data->r_line = NULL;
	data->errnum = 0;
	data->envp = env_clone(envp);
	temp_envp = retrieve_env_element(data->envp, "PATH");
	if (!temp_envp)
		update_env(data, DEFAULT_PATH);
	temp_envp = retrieve_env_element(data->envp, "PWD");
	if (!temp_envp)
	{
		output = (char *) malloc(BUFFER_SIZE);
		if (!output)
			return ;
		getcwd(output, BUFFER_SIZE);
		output = mem_realloc("PWD=", output, 0, 1);
		update_env(data, output);
		data->pwd = output;
	}
	else
		data->pwd = ft_strndup(temp_envp->var);
	update_env(data, "MINISHELL");
}

int	ft_cycle_commands(t_data *data)
{
	t_comd		*comd;
	int			result;

	setup_active_parent();
	comd = data->c_line;
	while (comd)
	{
		if (comd->result == RETURN_SUCCESSFUL && comd->comd)
		{
			if (comd->next)
				initialize_pipe(comd);
			result = run_builtin_comd(comd, data);
			if (result == RETURN_EXIT)
				return (RETURN_EXIT);
			if (result == RETURN_FALSE)
				perform_execve(comd, data);
		}
		else if (comd->result == RETURN_SUCCESSFUL && !comd->comd)
			return (ft_error_printer(comd, ERROR_INVALID_SNTX, ""));
		close_command_pipes(comd);
		comd = comd->next;
	}
	return (RETURN_SUCCESSFUL);
}
