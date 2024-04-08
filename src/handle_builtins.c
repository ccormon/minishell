/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:20 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/08 11:49:37 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Avec des token ce serait plus simple !
int	isbuiltins(t_arg *arg)
{
	if (ft_strcmp(arg->cmd_list->argv[0], "echo"))
		return (1);
	else if (ft_strcmp(arg->cmd_list->argv[0], "cd"))
		return (2);
	else if (ft_strcmp(arg->cmd_list->argv[0], "pwd"))
		return (3);
	else if (ft_strcmp(arg->cmd_list->argv[0], "export"))
		return (4);
	else if (ft_strcmp(arg->cmd_list->argv[0], "unset"))
		return (5);
	else if (ft_strcmp(arg->cmd_list->argv[0], "env"))
		return (6);
	else if (ft_strcmp(arg->cmd_list->argv[0], "exit"))
		return (7);
	else
		return (0);
}

bool	handle_builtins(t_arg *arg, t_cmd *cmd)
{
	int	code;

	if (!arg->cmd_list->output_redir[0])
		arg->cmd_list->output_fd = STDOUT_FILENO;
	code = isbuiltins(arg);
	if (code == 0)
		return (false);
	else if (code == 1)
		builtin_echo(arg, cmd->argv, cmd->output_fd);
	else if (code == 2)
		builtin_cd(arg, cmd->argv);
	else if (code == 3)
		builtin_pwd(arg, cmd->output_fd);
	else if (code == 4)
		builtin_export(arg, cmd->argv, cmd->output_fd);
	else if (code == 5)
		builtin_unset(arg, cmd->argv);
	else if (code == 6)
		builtin_env(arg, cmd->argv, cmd->output_fd);
	else if (code == 7)
		builtin_exit(arg, cmd->argv, true);
	return (true);
}
