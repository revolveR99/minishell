/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:41:52 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 20:08:18 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_interactive_parent(void)
{
	signal(SIGINT, &interactive_prnt_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_active_parent(void)
{
	signal(SIGINT, &active_prnt_sig_int);
	signal(SIGQUIT, &active_prnt_sig_quit);
}

void	setup_parent_heredoc(void)
{
	struct sigaction	main_process_sigaction;

	sigemptyset(&main_process_sigaction.sa_mask);
	main_process_sigaction.sa_flags = SA_SIGINFO;
	main_process_sigaction.sa_handler = &active_prnt_sig_int;
	sigaction(SIGINT, &main_process_sigaction, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_active_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
