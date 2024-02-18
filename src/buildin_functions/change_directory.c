/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:51:49 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 00:42:05 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	get_absolute_path(t_data *data, t_comd *comd)
{
	int	len;

	free(data->pwd);
	data->pwd = mem_realloc("PWD=", comd->argv->var, 0, 0);
	len = ft_strlen(data->pwd) - 1;
	if (data->pwd[len] == '/')
		data->pwd[len] = '\0';
}

static char	*rm_directory(char *path)
{
	char	*output;
	int		len;

	len = find_last_char(path, '/');
	if (len <= 4)
		output = ft_strndup("PWD=/");
	else
		output = retrieve_substr(path, 0, len);
	free(path);
	return (output);
}

static char	*add_directory(char *path, char *folder)
{
	char	*output;

	if (ft_strlen(path) > 5)
	{
		output = mem_realloc(path, "/", 1, 0);
		output = mem_realloc(output, folder, 1, 0);
	}
	else
		output = mem_realloc(path, folder, 1, 0);
	return (output);
}

static void	cd_2_relative_path(t_data *data, t_comd *comd)
{
	char		**new_path;
	int			i;
	struct stat	path_check;

	i = 0;
	if (ft_strcmp(comd->argv->var, ".") == 1)
		return ;
	new_path = ft_split(comd->argv->var, '/');
	while (new_path[i])
	{
		if (ft_strcmp(new_path[i], "..") == 1)
		{
			lstat(&data->pwd[4], &path_check);
			data->pwd = rm_directory(data->pwd);
			if (S_ISLNK(path_check.st_mode))
				chdir(&data->pwd[4]);
		}
		else
			data->pwd = add_directory(data->pwd, new_path[i]);
		i++;
	}
	free_chr_array(new_path);
}

int	change_directory(t_data *data, t_comd *comd)
{
	char		*old_pwd;
	struct stat	path_check;
	int			arg_count;

	arg_count = get_env_size(comd->argv);
	if (arg_count > 1)
		return (ft_error_printer(comd, ERROR_ARG_OVERFLOW, NULL));
	if (!comd->argv)
		return (RETURN_ERR);
	if (lstat(comd->argv->var, &path_check) == RETURN_ERR)
		return (ft_error_printer(comd, ERR_MISSING_DIRECTORY, comd->argv->var));
	comd->errnum = 0;
	if (comd == data->c_line)
	{
		chdir(comd->argv->var);
		old_pwd = mem_realloc("OLDPWD=", retrive_env("PWD", data->envp), 0, 0);
		update_env(data, old_pwd);
		free(old_pwd);
		if (comd->argv->var[0] == '/')
			get_absolute_path(data, comd);
		else
			cd_2_relative_path(data, comd);
		update_env(data, data->pwd);
	}
	return (RETURN_SUCCESSFUL);
}
