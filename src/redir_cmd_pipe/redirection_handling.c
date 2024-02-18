/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:50:30 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:24:01 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_return	input_redirect(t_comd *comd, t_redir *re)
{
	if (!re->next)
	{
		if (comd->fd->in > 2)
			close(comd->fd->in);
		comd->fd->in = open(re->file, O_RDONLY);
		if (comd->fd->in < 0)
		{
			ft_error_printer(comd, ERROR_UNKNOWN_FD, re->file);
			return (RETURN_ERR);
		}
	}
	else if (access(re->file, R_OK) == RETURN_ERR)
	{
		ft_error_printer(comd, ERROR_UNKNOWN_FD, re->file);
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

t_return	redir_dble_input(t_data *data, t_comd *comd, char *end_term)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERR)
		ft_error_printer(comd, errno, NULL);
	if (comd->fd->in > 2)
		close(comd->fd->in);
	comd->fd->in = fd[0];
	if (handle_heredoc(data, fd[1], end_term) == RETURN_ERR)
	{
		comd->errnum = 1;
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

t_return	output_rdrct(t_comd *comd, t_redir *re)
{
	if (comd->fd->out > 2)
		close(comd->fd->out);
	comd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_TRUNC, FILE_RIGHTS);
	if (comd->fd->out < 0)
	{
		ft_error_printer(comd, errno, NULL);
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

t_return	dble_output_redir(t_comd *comd, t_redir *re)
{
	if (comd->fd->out > 2)
		close(comd->fd->out);
	comd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_APPEND, FILE_RIGHTS);
	if (comd->fd->out < 0)
	{
		ft_error_printer(comd, errno, NULL);
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

int	handle_heredoc(t_data *data, int fd_out, char *end_term)
{
	char	*user_input;
	char	*temp;

	temp = mem_realloc(end_term, "\n", 0, 0);
	while (1)
	{
		ft_write_fd(STDOUT_FILENO, "> ");
		user_input = get_next_line(STDIN_FILENO);
		if (!user_input)
		{
			free((void *) temp);
			close(fd_out);
			return (RETURN_ERR);
		}
		user_input = ft_process_dollar_in_heredoc(user_input, data);
		if (ft_strcmp(user_input, temp))
			break ;
		ft_write_fd(fd_out, user_input);
		free((void *) user_input);
	}
	free((void *) temp);
	free((void *) user_input);
	close(fd_out);
	return (RETURN_SUCCESSFUL);
}
