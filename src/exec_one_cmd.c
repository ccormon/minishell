/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:25:31 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/14 16:20:01 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: exec_one_cmd
 * ----------------------
 * Executes a single command.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	exec_one_cmd(t_arg *arg, t_cmd *cmd)
{
	cmd->pid_child = fork();
	if (cmd->pid_child == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		if (cmd->input_redir[0])
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			close(cmd->input_fd);
		}
		if (cmd->output_redir[0])
		{
			dup2(cmd->output_fd, STDOUT_FILENO);
			close(cmd->output_fd);
		}
		if (cmd->cmd_path && access(cmd->cmd_path, X_OK) == 0)
			execve(cmd->cmd_path, cmd->argv, arg->envp);
		exec_errors(arg, cmd);
	}
	if (cmd->input_redir[0])
		close(cmd->input_fd);
	if (cmd->output_redir[0])
		close(cmd->output_fd);
	waitpid(cmd->pid_child, &cmd->status, 0);
	arg->exit_code = WEXITSTATUS(cmd->status);
}

/*
 * Function: handle_one_cmd
 * -------------------------
 * Handles execution of a single command.
 *
 * arg: Pointer to the argument structure.
 */
void	handle_one_cmd(t_arg *arg)
{
	if (!handle_redir(arg->cmd_list))
	{
		if (g_here_doc_fd == -1)
			return ;
		arg->exit_code = GENERAL_ERR;
		return ;
	}
	if (handle_builtins(arg, arg->cmd_list, arg->cmd_list->output_fd))
		return ;
	arg->paths = found_path(arg->envp);
	arg->cmd_list->cmd_path = ft_which(arg->paths, arg->cmd_list->argv[0]);
	free_tab(arg->paths);
	exec_one_cmd(arg, arg->cmd_list);
}
