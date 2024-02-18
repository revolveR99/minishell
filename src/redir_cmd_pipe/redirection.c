/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:50:48 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:24:01 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_redirections(t_comd *comd, t_redir *re)
{
	while (comd)
	{
		re = comd->re;
		while (re)
		{
			if (ft_strcmp(re->direct, "<"))
			{
				if (ft_handle_redirs(comd, re, input_redirect) == RETURN_ERR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">"))
			{
				if (ft_handle_redirs(comd, re, output_rdrct) == RETURN_ERR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">>"))
			{
				if (ft_handle_redirs(comd, re, dble_output_redir) == RETURN_ERR)
					break ;
			}
			re = re->next;
		}
		comd = comd->next;
	}
}
