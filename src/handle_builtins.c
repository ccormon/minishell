/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:20 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/13 14:53:41 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: ft_isbuiltin
 * -----------------------
 * Checks if a command is a built-in command.
 *
 * cmd: Pointer to the command structure.
 *
 * Returns: true if the command is a built-in command, false otherwise.
 */
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

/*
 * Function: handle_builtins
 * --------------------------
 * Handles execution of built-in commands.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 * output_fd: File descriptor for output redirection.
 *
 * Returns: true if the command is a built-in command and executed successfully,
 * false otherwise.
 */
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
