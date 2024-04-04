/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:25:31 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/04 18:03:18 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_one_cmd(t_arg *arg)
{
	// int	builtin_code;

	// builtin_code = isbuiltins(arg);
	// if (builtin_code != 0)
	// 	return (handle_builtins(arg, envp, builtin_code));
	arg->cmd_list->pid_child = fork();
	if (arg->cmd_list->pid_child == 0)
	{
		if (arg->cmd_list->input_redir[0])
		{
			dup2(arg->cmd_list->input_fd, STDIN_FILENO);
			close(arg->cmd_list->input_fd);
		}
		if (arg->cmd_list->output_redir[0])
		{
			dup2(arg->cmd_list->output_fd, STDOUT_FILENO);
			close(arg->cmd_list->output_fd);
		}
		execve(arg->cmd_list->cmd_path, arg->cmd_list->argv, arg->envp);
	}
	if (arg->cmd_list->input_redir[0])
		close(arg->cmd_list->input_fd);
	if (arg->cmd_list->output_redir[0])
		close(arg->cmd_list->output_fd);
	waitpid(arg->cmd_list->pid_child, &arg->cmd_list->status, 0);
	return (WEXITSTATUS(arg->cmd_list->status));
}

int	handle_one_cmd(t_arg *arg)
{
	arg->cmd_list->cmd_path = ft_which(arg->paths,
		arg->cmd_list->argv[0]);
	if (!arg->cmd_list->cmd_path)
		return (INVALID_CMD);
	if (arg->cmd_list->input_redir[0])
	{
		arg->cmd_list->input_fd = handle_redir_input(arg->cmd_list);
		if (arg->cmd_list->input_fd == -1)
			return (GENERAL_ERR);
	}
	// else
	// 	arg->cmd_list->input_fd = STDIN_FILENO;
	if (arg->cmd_list->output_redir[0])
	{
		arg->cmd_list->output_fd = handle_redir_output(arg->cmd_list);
		if (arg->cmd_list->output_fd == -1)
			return (GENERAL_ERR);
	}
	// else
	// 	arg->cmd_list->output_fd = STDOUT_FILENO;
	return (exec_one_cmd(arg));
}
