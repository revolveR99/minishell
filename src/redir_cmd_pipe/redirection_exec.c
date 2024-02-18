/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:50:40 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 02:24:01 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*create_new_redir(char *direct, char *file)
{
	t_redir	*new_element;

	new_element = (t_redir *) malloc(sizeof(t_redir));
	if (!new_element)
		return (NULL);
	new_element->direct = ft_strndup(direct);
	new_element->file = ft_strndup(file);
	new_element->next = NULL;
	return (new_element);
}

t_redir	*find_last_redir(t_redir *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	append_redir_to_list(t_redir **lst, t_redir *new)
{
	if (!*lst)
		*lst = new;
	else
		find_last_redir(*lst)->next = new;
}

void	delete_redir_list(t_redir **re)
{
	t_redir	*re_temp;

	while (*re)
	{
		re_temp = *re;
		*re = (*re)->next;
		free((void *) re_temp->direct);
		free((void *) re_temp->file);
		re_temp->direct = NULL;
		re_temp->file = NULL;
		free((void *) re_temp);
		re_temp = NULL;
	}
	*re = NULL;
}

void	process_and_add_redir(t_data *data, t_parser *parser)
{
	char	*file;
	char	*direct;

	direct = parser->token;
	parser->token = NULL;
	file = ft_retrieve_next_token(parser, data);
	append_redir_to_list(&parser->comd->re, create_new_redir(direct, file));
	free((void *) direct);
	free((void *) file);
}
