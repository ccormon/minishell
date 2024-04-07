/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:55:56 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/07 20:40:12 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

// what if HOME is manually changed 
static void	exec_cd(t_arg *arg, char *path)
{
	DIR	*dir;

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
		rewrite_evar(arg, "OLDPWD=", //change it, when PWD is unset segfault do not malloc second one
			ft_strdup(find_str(arg->envp, "PWD=", 4)));
		rewrite_evar(arg, "PWD=", getcwd(NULL, 0));
	}
}

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
