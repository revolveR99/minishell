/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:39:51 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 04:00:00 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_shell_loop(t_data *data)
{
	while (1)
	{
		handle_readline(data);
		if (data->r_line == NULL || handle_commands(data) == RETURN_EXIT)
			break ;
		cleanup_after_execution(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ft_init(&data, envp);
	setup_interactive_parent();
	(void)argc;
	(void)argv;
	process_shell_loop(&data);
	exit_shell(&data);
}
