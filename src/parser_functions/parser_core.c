/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:09 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:20:06 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parse_shell_input(t_data *data)
{
	t_parser	parser;

	ft_initialize_parser_state(&parser, data);
	while (*parser.temp)
	{
		parser.len = ft_find_token_length(parser.temp, &parser.inside_echo);
		parser.token = retrieve_substr(parser.temp, 0, parser.len);
		parser.parse_result = ft_process_command_token(data, &parser);
		if (parser.parse_result == RETURN_ERR)
			break ;
		if (parser.parse_result == RETURN_TRUE)
			process_and_add_redir(data, &parser);
		if (parser.parse_result == RETURN_FALSE)
			ft_process_and_add_command_arg(data, &parser);
		ft_free((void *) parser.token);
		if (parser.inside_echo == 0)
			parser.temp = ft_advance_past_leading_whitespaces(parser.temp);
		else
			ft_skip_echo_whitespaces(&parser);
		if (ft_strcmp(parser.comd->comd, "echo"))
			parser.inside_echo = 1;
	}
}

void	ft_initialize_parser_state(t_parser *parser, t_data *data)
{
	data->c_line = new_commd_element();
	parser->inside_echo = 0;
	parser->parse_result = 0;
	parser->comd = data->c_line;
	parser->temp = data->r_line;
	parser->temp = ft_advance_past_leading_whitespaces(parser->temp);
}

int	ft_check_command_token(const char *token)
{
	if (token[0] == '|')
		return (RETURN_PIPE);
	if (strcmp(token, "<") == 0 || strcmp(token, ">") == 0
		|| strcmp(token, "<<") == 0 || strcmp(token, ">>") == 0)
		return (RETURN_TRUE);
	return (RETURN_FALSE);
}

int	ft_process_command_token(t_data *data, t_parser *parser)
{
	int	token_type;

	(void) data;
	parser->temp += parser->len;
	token_type = ft_check_command_token(parser->token);
	if (token_type == RETURN_PIPE)
	{
		parser->comd->next = new_commd_element();
		parser->comd->result = RETURN_SUCCESSFUL;
		parser->comd = parser->comd->next;
	}
	return (token_type);
}

void	ft_skip_echo_whitespaces(t_parser *parser)
{
	parser->len = ft_count_leading_whitespaces(parser->temp);
	if (parser->len > 0)
		parser->temp += parser->len;
}
