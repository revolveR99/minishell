/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:51:07 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/15 12:08:43 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_error_printer(t_comd *comd, int ernbr, char *file)
{
	ft_write_fd(comd->fd->err, PROMPT);
	if (ernbr == ERROR_COMD_NO)
		handle_file_comd_error(comd);
	else if (ernbr == ERROR_FILE)
		handle_file_error(comd);
	else if (ernbr == ERROR_INVALID_SNTX)
		handle_syntax_error(comd, file);
	else if (ernbr == ERROR_NOT_VALID)
		handle_invalid_error(comd, file);
	else if (ernbr == NUM_ERROR)
		handle_numeric_error(comd, file);
	else if (ernbr == ERROR_ARG_OVERFLOW)
		handle_arg_overflow(comd);
	else if (ernbr == ERR_MISSING_DIRECTORY)
		error_folder_not_found(comd, file);
	else if (ernbr == ERROR_UNKNOWN_FD)
		err_unknown_fd(comd, file);
	else
		handle_else_error(comd, ernbr);
	return (RETURN_ERR);
}

int	err_code(t_comd *comd)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < 255)
	{
		ft_write_fd(comd->fd->out, "error code ");
		temp = int_to_str(i);
		temp = mem_realloc(temp, " ", 1, 0);
		ft_write_fd(comd->fd->out, temp);
		ft_write_fd_nl(comd->fd->out, strerror(i));
		i++;
		free((void *) temp);
	}
	return (RETURN_SUCCESSFUL);
}
