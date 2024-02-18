/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:58:51 by kryxaurus         #+#    #+#             */
/*   Updated: 2024/01/16 20:23:14 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_process_and_add_command_arg(t_data *data, t_parser *parser)
{
	char	*temp;

	temp = ft_process_token_for_quotes_vars(parser, data);
	if (parser->comd->comd)
		add_back_list(&parser->comd->argv, lst_new(temp));
	else
	{
		parser->comd->comd = ft_strndup(temp);
		parser->comd->result = RETURN_SUCCESSFUL;
	}
	free((void *) temp);
}
