/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:55:56 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/14 16:37:59 by sdemaude         ###   ########.fr       */
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
		ft_putstr_fd("cd : HOME not set\n", STDERR_FILENO);
		arg->exit_code = GENERAL_ERR;
		return ;
	}
	dir = opendir(path);
	if (!dir)
	{
		perror("cd");
		arg->exit_code = GENERAL_ERR;
		return ;
	}
	closedir(dir);
	chdir(path);
	free(arg->pwd);
	arg->pwd = getcwd(NULL, 0);
	rewrite_evar(arg, "OLDPWD=", find_str(arg->envp, "PWD=", 4));
	rewrite_evar(arg, "PWD=", arg->pwd);
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
	arg->exit_code = EXIT_SUCCESS;
	if (!argv[1])
		exec_cd(arg, find_str(arg->envp, "HOME=", 5));
	else if (!argv[2])
		exec_cd(arg, argv[1]);
	else
	{
		ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
		arg->exit_code = GENERAL_ERR;
	}
}
