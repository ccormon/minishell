/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/03 10:28:04 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe(t_arg *arg, int cmd_no)
{
	if (cmd_no == 0)
		pipe(arg->pipe_fd[cmd_no % 2]);
	else if (!arg->cmd_list->next)
	{
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
	}
	else
	{
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
		pipe(arg->pipe_fd[cmd_no % 2]);
	}
	if (arg->cmd_list->input_redir)
	{
		arg->cmd_list->input_fd = handle_redir_input(arg->cmd_list);
		if (arg->cmd_list->input_fd == -1)
			return (GENERAL_ERR);
	}
	if (arg->cmd_list->output_redir)
	{
		arg->cmd_list->output_fd = handle_redir_output(arg->cmd_list);
		if (arg->cmd_list->output_fd == -1)
			return (GENERAL_ERR);
	}
	return (0);
}

void	exec_cmd(t_arg *arg, int cmd_no, char **envp)
{
	// int	builtin_code;

	// builtin_code = isbuiltins(arg);
	// if (builtin_code != 0)
	// 	return (handle_builtins(arg, envp, builtin_code));
	arg->cmd_list->pid_child = fork();
	if (arg->cmd_list->pid_child == 0)
	{
		dup2(arg->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
		close(arg->pipe_fd[(cmd_no + 1) % 2][0]);
		dup2(arg->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
		close(arg->pipe_fd[cmd_no % 2][0]);
		close(arg->pipe_fd[cmd_no % 2][1]);
		execve(arg->cmd_list->cmd_path, arg->cmd_list->arguments, envp);
	}
}

int	wait_childs(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	while (cmd)
	{
		waitpid(cmd->pid_child, &cmd->status, 0);
		if (WEXITSTATUS(cmd->status) != 0)
			exit_code = WEXITSTATUS(cmd->status);
		cmd = cmd->next;
	}
	return(exit_code);
}

int	handle_multiple_cmd(t_arg *param, char **envp)
{
	t_arg	*arg;
	int		exit_code;
	int		cmd_no;

	arg = param;
	cmd_no = 0;
	while (arg->cmd_list->next)
	{
		exit_code = ft_pipe(arg, cmd_no);
		if (exit_code != 0)
			return (exit_code);
		arg->cmd_list->cmd_path = ft_which(arg->paths,
			arg->cmd_list->arguments[0]);
		exec_cmd(arg, cmd_no, envp);
		arg->cmd_list = arg->cmd_list->next;
	}
	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	exit_code = wait_childs(param->cmd_list);
	return (exit_code);
}

void	executing(t_arg *arg, char **envp)
{
	if (!arg->cmd_list->next)
	{
		// execute one command
		arg->exit_code = handle_one_cmd(arg, envp);
	}
	else
	{
		// execute multiple command
		arg->exit_code = handle_multiple_cmd(arg, envp);
	}
}
