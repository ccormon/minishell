/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:55:56 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:07:57 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

/*
 * Function: exec_cd
 * -----------------
 * Executes the 'cd' built-in command.
 *
 * arg:  Pointer to a structure containing command arguments and settings.
 * path: Path to change the directory to.
 */
static void	exec_cd(t_arg *arg, char *path)
{
	DIR		*dir;

	if (!path)
	{
		ft_putstr_fd("cd : HOME not set\n", 2);
		arg->exit_code = 1;
		return ;
	}
	dir = opendir(path);
	if (!dir)
	{
		perror("cd");
		arg->exit_code = 1;
		return ;
	}
	closedir(dir);
	if (arg->nb_cmd == 1)
	{
		chdir(path);
		free(arg->pwd);
		arg->pwd = getcwd(NULL, 0);
		rewrite_evar(arg, "OLDPWD=", find_str(arg->envp, "PWD=", 4));
		rewrite_evar(arg, "PWD=", arg->pwd);
	}
}

/*
 * Function: builtin_cd
 * ---------------------
 * Executes the 'cd' built-in command.
 *
 * arg:   Pointer to a structure containing command arguments and settings.
 * argv:  Array of command arguments.
 */
void	builtin_cd(t_arg *arg, char **argv)
{
	arg->exit_code = 0;
	if (!argv[1])
		exec_cd(arg, find_str(arg->envp, "HOME=", 5));
	else if (!argv[2])
		exec_cd(arg, argv[1]);
	else
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		arg->exit_code = 1;
	}
}
