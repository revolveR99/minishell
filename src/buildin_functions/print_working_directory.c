/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:52:54 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/14 21:20:50 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_current_path(t_data *data, t_comd *comd)
{
	ft_write_fd_nl(comd->fd->out, &data->pwd[ft_pos_in_string
		(data->pwd, '=') + 1]);
	return (RETURN_SUCCESSFUL);
}
