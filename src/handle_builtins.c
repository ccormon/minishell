/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:20 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/11 13:09:46 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isbuiltin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo")
		|| ft_strcmp(cmd->argv[0], "cd")
		|| ft_strcmp(cmd->argv[0], "pwd")
		|| ft_strcmp(cmd->argv[0], "export")
		|| ft_strcmp(cmd->argv[0], "unset")
		|| ft_strcmp(cmd->argv[0], "env")
		|| ft_strcmp(cmd->argv[0], "exit"))
		return (true);
	return (false);
}

bool	handle_builtins(t_arg *arg, t_cmd *cmd, int output_fd)
{
	if (ft_strcmp(cmd->argv[0], "echo"))
		builtin_echo(arg, cmd->argv, output_fd);
	else if (ft_strcmp(cmd->argv[0], "cd"))
		builtin_cd(arg, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "pwd"))
		builtin_pwd(arg, output_fd);
	else if (ft_strcmp(cmd->argv[0], "export"))
		builtin_export(arg, cmd->argv, output_fd);
	else if (ft_strcmp(cmd->argv[0], "unset"))
		builtin_unset(arg, cmd->argv);
	else if (ft_strcmp(cmd->argv[0], "env"))
		builtin_env(arg, cmd->argv, output_fd);
	else if (ft_strcmp(cmd->argv[0], "exit"))
		builtin_exit(arg, cmd->argv, true);
	else
		return (false);
	return (true);
}
