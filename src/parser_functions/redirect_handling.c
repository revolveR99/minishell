/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:35 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:24:01 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_return	ft_process_all_command_redirections(t_data *data)
{
	t_redir		*re_temp;
	t_comd		*comd_temp;

	comd_temp = data->c_line;
	while (comd_temp)
	{
		re_temp = comd_temp->re;
		while (re_temp)
		{
			if (ft_strcmp(re_temp->direct, "<<"))
				if (ft_prepare_heredoc_redirection(data, comd_temp,
						re_temp->file) == RETURN_ERR)
					return (RETURN_ERR);
			re_temp = re_temp->next;
		}
		comd_temp = comd_temp->next;
	}
	comd_temp = data->c_line;
	execute_redirections(comd_temp, re_temp);
	return (RETURN_SUCCESSFUL);
}

t_return	ft_handle_redirs(t_comd *comd, t_redir *re,
	t_return (*redirect)(t_comd *, t_redir *))
{
	if (re->file[0] == '\0' || re->file[0] == '<' || re->file[0] == '>'
		|| re->file[0] == '|' || re->file[0] == '*')
	{
		comd->result = RETURN_ERR;
		ft_error_printer(comd, ERROR_INVALID_SNTX, re->file);
		return (RETURN_ERR);
	}
	if (redirect(comd, re) == RETURN_ERR)
	{
		comd->result = RETURN_ERR;
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

int	ft_validate_redirection_token(t_comd *comd, char *file)
{
	if (file[0] == '\0' || ft_validate_heredoc_terminator
		(file) == RETURN_FALSE)
	{
		ft_error_printer(comd, ERROR_INVALID_SNTX, file);
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

int	ft_prepare_heredoc_redirection(t_data *data, t_comd *comd, char *end_term)
{
	if (ft_validate_redirection_token(comd, end_term) == RETURN_ERR)
	{
		return (RETURN_ERR);
	}
	setup_parent_heredoc();
	comd->result = redir_dble_input(data, comd, end_term);
	setup_interactive_parent();
	if (comd->result == RETURN_ERR)
	{
		data->errnum = 1;
		return (RETURN_ERR);
	}
	return (RETURN_SUCCESSFUL);
}

int	ft_validate_heredoc_terminator(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A'
				|| s[i] > 'Z') && (s[i] < '0' || s[i] > '9'))
			return (RETURN_FALSE);
		i++;
	}
	return (RETURN_TRUE);
}
