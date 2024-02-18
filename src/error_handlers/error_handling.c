/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:51:20 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 00:26:15 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_file_comd_error(t_comd *comd)
{
	ft_write_fd(comd->fd->err, comd->comd);
	if (find_char_in_str(comd->comd, '/'))
		ft_write_fd(comd->fd->err, ": no such file or directory\n");
	else
		ft_write_fd(comd->fd->err, ": command not found\n");
	comd->errnum = 127;
}

void	handle_syntax_error(t_comd *comd, char *token)
{
	ft_write_fd(comd->fd->err, "syntax error near unexpected token `");
	if (token && token[0] == '\0')
		ft_write_fd(comd->fd->err, "newline");
	else
		ft_write_fd(comd->fd->err, token);
	ft_write_fd(comd->fd->err, "'\n");
	comd->errnum = 258;
}

void	handle_invalid_error(t_comd *comd, char *token)
{
	ft_write_fd(comd->fd->err, comd->comd);
	ft_write_fd(comd->fd->err, ": `");
	ft_write_fd(comd->fd->err, token);
	ft_write_fd(comd->fd->err, "': not a valid identifier\n");
	comd->errnum = 1;
}

void	handle_numeric_error(t_comd *comd, char *token)
{
	ft_write_fd(comd->fd->err, comd->comd);
	ft_write_fd(comd->fd->err, ": ");
	ft_write_fd(comd->fd->err, token);
	ft_write_fd(comd->fd->err, ": numeric argument required\n");
	comd->errnum = 2;
}

void	handle_arg_overflow(t_comd *comd)
{
	ft_write_fd(comd->fd->err, comd->argv->var);
	ft_write_fd(comd->fd->err, ": too many arguments\n");
	comd->errnum = 1;
}
