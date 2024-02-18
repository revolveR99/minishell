/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:28 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 01:02:13 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	retrn_via_err(t_comd *comd)
{
	ft_write_fd(comd->fd->err, "exit\n");
	return (RETURN_EXIT);
}

int	handle_exit_comd(t_comd *comd, t_data *data)
{
	int	i;

	i = get_env_size(comd->argv);
	if (i != 0 && !only_number(comd->argv->var))
	{
		comd->errnum = 255;
		ft_error_printer(comd, NUM_ERROR, comd->argv->var);
		if (comd == data->c_line && !data->c_line->next)
			return (retrn_via_err(comd));
	}
	if (i > 1)
	{
		ft_write_fd(comd->fd->err, "exit\n");
		return (ft_error_printer(comd, ERROR_ARG_OVERFLOW, NULL));
	}
	if (i >= 1)
		comd->errnum = (unsigned char) ft_atoi(comd->argv->var);
	if (comd != data->c_line || data->c_line->next)
		return (RETURN_ERR);
	ft_write_fd(comd->fd->err, "exit\n");
	return (RETURN_EXIT);
}

int	only_number(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > '9' || input[i] < '0')
		{
			if (i > 0 || (input[i] != '+' && input[i] != '-')
				|| input[i + 1] < '0' || input[i + 1] > '9')
				return (0);
		}
		i++;
	}
	return (1);
}
