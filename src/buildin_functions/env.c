/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:13 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/15 10:55:10 by zabdulza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	base_env(t_data *data, t_comd *comd)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (find_char_in_str(temp->var, '='))
			ft_write_fd_nl(comd->fd->out, temp->var);
		temp = temp->next;
	}
	return (RETURN_SUCCESSFUL);
}

char	*get_variable(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[i]) || (!ft_isalpha(s[i]) && s[i] != '_'))
		return (retrieve_substr(s, 0, 1));
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r') || s[i] == '#')
			break ;
		else if (s[i] == '\"' || s[i] == '\'' || s[i] == '$' || s[i] == '=')
			break ;
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	return (retrieve_substr(s, 0, i));
}

int	cmpare_varable(char *var_name, char *var_elem)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (var_name[i] != var_elem[i])
			return (0);
		i++;
	}
	if (var_elem[i] == '=' || var_elem[i] == '\0')
		return (1);
	return (0);
}

t_envp	*retrieve_env_element(t_envp *lst, char *var)
{
	t_envp	*temp;
	char	*var_name;

	temp = lst;
	while (temp)
	{
		var_name = get_variable(var);
		if (cmpare_varable(var_name, temp->var))
		{
			free((void *) var_name);
			return (temp);
		}
		if (var_name)
			free((void *) var_name);
		temp = temp->next;
	}
	return (NULL);
}

int	get_env_size(t_envp *envp)
{
	t_envp	*temp;
	int		i;

	temp = envp;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
