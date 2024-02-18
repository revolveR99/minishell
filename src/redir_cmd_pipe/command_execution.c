/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:43:01 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/14 21:23:46 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	first_command(t_comd *comd, t_data *data)
{
	if (comd != data->c_line)
		return (0);
	return (1);
}

t_comd	*last_command(t_comd *comd)
{
	t_comd	*temp;

	temp = comd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
