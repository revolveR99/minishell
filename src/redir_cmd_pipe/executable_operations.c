/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:43:10 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 15:10:43 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	perform_execve(t_comd *comd, t_data *data)
{
	char	**paths;
	char	*comd_path;

	paths = ft_split(retrive_env("PATH", data->envp), ':');
	if (!paths)
		return (ft_error_printer(comd, ERROR_FILE, NULL));
	comd_path = path_checking(comd->comd, paths);
	free_chr_array(paths);
	if (!comd_path)
		return (ft_error_printer(comd, ERROR_COMD_NO, NULL));
	if (comd->fd->in == RETURN_ERR)
	{
		free(comd_path);
		return (1);
	}
	update_env(data, mem_realloc("_=", comd_path, 0, 0));
	comd->pid = fork();
	if (comd->pid < 0)
		return (ft_error_printer(comd, errno, NULL));
	if (comd->pid == 0)
		run_child_process(comd, data, comd_path);
	free((void *) comd_path);
	return (0);
}

void	run_child_process(t_comd *comd, t_data *data, char *comd_path)
{
	char	**envp;
	char	**argv;

	setup_active_child();
	pipe_joining(comd);
	close_child_fd(comd, data);
	envp = form_envp_array(data->envp);
	argv = build_argument_array(comd);
	if (execve(comd_path, argv, envp) == RETURN_ERR)
		ft_error_printer(comd, errno, NULL);
	close_command_pipes(comd);
	free_chr_array(envp);
	free_chr_array(argv);
	delete_list(&data->envp);
	delete_list(&comd->argv);
	cleanup_command(&data->c_line);
	free((void *) data->pwd);
	free((void *) comd_path);
	exit(0);
}

char	**build_argument_array(t_comd *comd)
{
	char	**output;
	t_envp	*temp;
	int		i;

	output = (char **) malloc((get_env_size
				(comd->argv) + 2) * sizeof(char *));
	if (!output)
		return (NULL);
	temp = comd->argv;
	output[0] = ft_strndup(comd->comd);
	i = 1;
	while (temp)
	{
		output[i] = ft_strndup(temp->var);
		temp = temp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	**form_envp_array(t_envp *envp)
{
	char	**output;
	t_envp	*temp;
	int		i;

	output = (char **) malloc((get_env_size(envp) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp)
	{
		output[i] = ft_strndup(temp->var);
		temp = temp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	*path_checking(char *comd, char **paths)
{
	char	*test_path;
	int		i;

	i = 0;
	if (find_char_in_str(comd, '/'))
	{
		if (access(comd, F_OK) == 0)
			return (ft_strndup(comd));
	}
	while (paths && paths[i])
	{
		test_path = mem_realloc(paths[i], "/", 0, 0);
		test_path = mem_realloc(test_path, comd, 1, 0);
		if (access(test_path, F_OK) == RETURN_SUCCESSFUL)
			return (test_path);
		free((void *) test_path);
		i++;
	}
	return (NULL);
}
