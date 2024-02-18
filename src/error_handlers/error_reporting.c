/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:51:34 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/14 21:23:12 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_folder_not_found(t_comd *comd, char *token)
{
	ft_write_fd(comd->fd->err, comd->comd);
	ft_write_fd(comd->fd->err, ": ");
	ft_write_fd(comd->fd->err, token);
	ft_write_fd(comd->fd->err, ": No such file or directory\n");
	comd->errnum = 1;
}

void	handle_else_error(t_comd *comd, int errnum)
{
	ft_write_fd(comd->fd->err, comd->comd);
	ft_write_fd(comd->fd->err, ": ");
	ft_write_fd_nl(comd->fd->err, strerror(errnum));
	comd->errnum = errnum;
}

void	err_unknown_fd(t_comd *comd, char *token)
{
	ft_write_fd(comd->fd->err, token);
	ft_write_fd(comd->fd->err, ": No such file or directory\n");
	comd->errnum = 1;
}

void	handle_file_error(t_comd *comd)
{
	ft_write_fd(comd->fd->err, comd->comd);
	ft_write_fd(comd->fd->err, ": No such file or directory\n");
	comd->errnum = 127;
}
