/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:43 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/15 10:40:57 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_retrieve_next_token(t_parser *parser, t_data *data)
{
	char	*output;
	int		len;

	parser->temp = ft_advance_past_leading_whitespaces(parser->temp);
	len = ft_find_token_length(parser->temp, 0);
	parser->token = retrieve_substr(parser->temp, 0, len);
	output = ft_process_token_for_quotes_vars(parser, data);
	free(parser->token);
	parser->token = NULL;
	parser->temp += len;
	return (output);
}
