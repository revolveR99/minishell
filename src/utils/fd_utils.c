/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:40:47 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/16 03:44:26 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_write_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void	ft_write_fd_nl(int fd, char *str)
{
	ft_write_fd(fd, str);
	write(fd, "\n", 1);
}
