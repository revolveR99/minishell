/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:50:21 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 15:10:45 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	initialize_pipe(t_comd *comd)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERR)
		return (ft_error_printer(comd, errno, NULL));
	if (comd->fd->out == STDOUT_FILENO)
		comd->fd->out = fd[1];
	else
		close(fd[1]);
	if (comd->next->fd->in == STDIN_FILENO)
		comd->next->fd->in = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	pipe_joining(t_comd *comd)
{
	if (comd->fd->in != STDIN_FILENO && comd->fd->in != RETURN_ERR)
	{
		dup2(comd->fd->in, STDIN_FILENO);
		close(comd->fd->in);
	}
	if (comd->fd->out != STDOUT_FILENO)
	{
		dup2(comd->fd->out, STDOUT_FILENO);
		close(comd->fd->out);
	}
	return (0);
}

int	close_command_pipes(t_comd *comd)
{
	if (comd->fd->in != STDIN_FILENO && comd->fd->in != RETURN_ERR)
		close(comd->fd->in);
	if (comd->fd->out != STDOUT_FILENO)
		close(comd->fd->out);
	return (0);
}

void	close_child_fd(t_comd *comd, t_data *data)
{
	t_comd	*temp;

	temp = data->c_line;
	while (temp)
	{
		if (temp != comd)
			close_command_pipes(temp);
		temp = temp->next;
	}
}
