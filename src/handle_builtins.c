/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:20 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/02 14:28:23 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isbuiltins(t_arg *arg)
{
	if (ft_strcmp(arg->cmd_list->arguments[0], "echo"))
		return (1);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "cd"))
		return (2);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "pwd"))
		return (3);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "export"))
		return (4);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "unset"))
		return (5);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "env"))
		return (6);
	else if (ft_strcmp(arg->cmd_list->arguments[0], "exit"))
		return (7);
	else
		return (0);
}

int	handle_builtins(t_arg *arg, char **envp, int builtin_code)
{
	if (!arg->cmd_list->output_redir)
		arg->cmd_list->output_fd = STDOUT_FILENO;
	if (builtin_code == 1)
		return (builtin_echo(arg));
	else if (builtin_code == 2)
		return (builtin_cd(arg));
	else if (builtin_code == 3)
		return (builtin_pwd(arg, envp));
	else if (builtin_code == 4)
		return (builtin_export(arg));
	else if (builtin_code == 5)
		return (buitlin_unset(arg, envp));
	else if (builtin_code == 6)
		return (builtin_env(arg, envp));
	else if (builtin_code == 7)
		return (builtin_exit(arg));
	else
		return (GENERAL_ERR);
}
