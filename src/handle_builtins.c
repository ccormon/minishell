/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:20 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/09 19:00:57 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	handle_builtins(t_arg *arg, t_cmd *cmd)
{
	if (!arg->cmd_list->output_redir[0])
		arg->cmd_list->output_fd = STDOUT_FILENO;
	if (ft_strcmp(arg->cmd_list->argv[0], "echo"))
		builtin_echo(arg, cmd->argv, cmd->output_fd);
	else if (ft_strcmp(arg->cmd_list->argv[0], "cd"))
		builtin_cd(arg, cmd->argv);
	else if (ft_strcmp(arg->cmd_list->argv[0], "pwd"))
		builtin_pwd(arg, cmd->output_fd);
	else if (ft_strcmp(arg->cmd_list->argv[0], "export"))
		builtin_export(arg, cmd->argv, cmd->output_fd);
	else if (ft_strcmp(arg->cmd_list->argv[0], "unset"))
		builtin_unset(arg, cmd->argv);
	else if (ft_strcmp(arg->cmd_list->argv[0], "env"))
		builtin_env(arg, cmd->argv, cmd->output_fd);
	else if (ft_strcmp(arg->cmd_list->argv[0], "exit"))
		builtin_exit(arg, cmd->argv, true);
	else
		return (false);
	return (true);
}
