/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:23 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 01:10:17 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// for testing 
// export TEST_VAR="Hello, World!"
// echo "The value of TEST_VAR is: $TEST_VAR"
// echo 'The value of TEST_VAR is: $TEST_VAR'

// I made 2 different functions for ft_process_dble_quoted_segm, 
// because in shell
// echo '$VAR' prints $VAR and "$VAR" prints whats inside the variable VAR

void	ft_process_dble_quoted_segm(t_parse *check, char *input, t_data *data)
{
	if (check->i > 0)
		ft_add_substring_to_list(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '$')
			if ((!ft_iswhitespace(input[check->i + 1])
					&& input[check->i + 2] != '\0'))
				ft_process_dollar(check, input, data);
		if (input[check->i] == '\"')
		{
			ft_add_substring_to_list(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

void	ft_process_single_quoted_segment(t_parse *check, char *input)
{
	if (check->i > 0)
		ft_add_substring_to_list(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '\'')
		{
			ft_add_substring_to_list(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

void	ft_add_substring_to_list(t_parse *check, char *input)
{
	char	*temp;

	temp = retrieve_substr(input, check->start, check->i - check->start);
	add_back_list(&check->str, lst_new(temp));
	free((void *) temp);
	check->i_string++;
}

char	*ft_process_token_for_quotes_vars(t_parser *par, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (par->token[check.i])
	{
		if (par->token[check.i] == '\"')
			ft_process_dble_quoted_segm(&check, par->token, data);
		else if (par->token[check.i] == '\'')
			ft_process_single_quoted_segment(&check, par->token);
		else if (par->token[check.i] == '$')
			ft_process_dollar(&check, par->token, data);
		else if (par->token[check.i] == '#' && check.i == 0)
			return (ft_nullify_input_on_hash(par->temp));
		check.i++;
	}
	if (check.i_string == 0)
		return (ft_strndup(par->token));
	if (check.start != check.i)
		add_back_list(&check.str, lst_new(&par->token[check.start]));
	return (ft_assemble_string_from_list(check.str));
}

char	*ft_process_dollar_in_heredoc(char *token, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (token[check.i])
	{
		if (token[check.i] == '$')
			ft_process_dollar(&check, token, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (token);
	if (check.start != check.i)
		add_back_list(&check.str, lst_new(&token[check.start]));
	free(token);
	return (ft_assemble_string_from_list(check.str));
}
