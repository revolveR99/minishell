/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:51:55 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 08:44:54 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_echo(t_comd *comd)
{
	t_envp	*argv_temp;
	t_envp	*valid_argv;
	int		new_line;

	new_line = 1;
	argv_temp = comd->argv;
	while (argv_temp)
	{
		if (option_is_valid(argv_temp->var))
			new_line = 0;
		else
			break ;
		argv_temp = argv_temp->next;
	}
	valid_argv = argv_temp;
	while (argv_temp)
	{
		if (argv_temp != valid_argv)
			ft_write_fd(comd->fd->out, " ");
		ft_write_fd(comd->fd->out, argv_temp->var);
		argv_temp = argv_temp->next;
	}
	if (new_line)
		write(comd->fd->out, "\n", 1);
	return (RETURN_SUCCESSFUL);
}

int	option_is_valid(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '-')
		return (0);
	i++;
	while (input[i])
	{
		if (input[i] != 'n' && input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
