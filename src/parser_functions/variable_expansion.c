/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:28 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:13:50 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_process_dollar(t_parse *check, char *input, t_data *data)
{
	char	*temp;

	if (check->i > 0)
		ft_add_substring_to_list(check, input);
	temp = get_variable(&input[check->i + 1]);
	if (validity_check(temp) == 0 && temp[0] != '?')
		temp[0] = '\0';
	if (ft_strncmp(temp, "?", 1) == 0)
		ft_process_question_mark(check, data);
	else if (ft_strncmp(&input[check->i + 1], "\0", 1) == 0
		|| ft_strncmp(&input[check->i + 1], "\'", 1) == 1
		|| ft_strncmp(&input[check->i + 1], "\"", 1) == 1)
		add_back_list(&check->str, lst_new("$"));
	else
	{
		add_back_list(&check->str, lst_new(retrive_env(temp, data->envp)));
	}
	check->i_string++;
	check->i += ft_strlen(temp);
	check->start = check->i + 1;
	free((void *) temp);
}

char	*ft_nullify_input_on_hash(char *input)
{
	input[0] = '\0';
	return (NULL);
}

void	ft_process_question_mark(t_parse *check, t_data *data)
{
	char	*temp2;

	temp2 = int_to_str((long) data->errnum);
	add_back_list(&check->str, lst_new(temp2));
	free((void *) temp2);
}

char	*ft_assemble_string_from_list(t_envp *list)
{
	char	*output;
	t_envp	*temp;

	temp = list;
	output = (char *) malloc(1);
	output[0] = '\0';
	while (temp)
	{
		output = mem_realloc(output, temp->var, 1, 0);
		temp = temp->next;
	}
	delete_list(&list);
	return (output);
}
