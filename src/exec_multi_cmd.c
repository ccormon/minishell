/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/12 12:52:40 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_first_cmd(t_arg *arg, t_cmd *cmd)
{
	pipe(arg->pipe_fd);
	if (cmd->input_fd != STDIN_FILENO)
		arg->cmd_read_fd = cmd->input_fd;
	else
		arg->cmd_read_fd = dup(STDIN_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
	{
		close(arg->pipe_fd[1]);
		arg->pipe_fd[1] = cmd->output_fd;
	}
}

void	ft_pipe_last_cmd(t_arg *arg, t_cmd *cmd)
{
	close(arg->cmd_read_fd);
	if (cmd->input_fd != STDIN_FILENO)
		arg->cmd_read_fd = cmd->input_fd;
	else
		arg->cmd_read_fd = arg->pipe_fd[0];
	close(arg->pipe_fd[1]);
	if (cmd->output_fd != STDOUT_FILENO)
		arg->pipe_fd[1] = cmd->output_fd;
	else
		arg->pipe_fd[1] = dup(STDOUT_FILENO);
}

void	ft_pipe_middle_cmd(t_arg *arg, t_cmd *cmd)
{
	close(arg->cmd_read_fd);
	if (cmd->input_fd != STDIN_FILENO)
		arg->cmd_read_fd = cmd->input_fd;
	else
		arg->cmd_read_fd = arg->pipe_fd[0];
	close(arg->pipe_fd[1]);
	pipe(arg->pipe_fd);
	if (cmd->output_fd != STDOUT_FILENO)
	{
		close(arg->pipe_fd[1]);
		arg->pipe_fd[1] = cmd->output_fd;
	}
}

void	ft_pipe(t_arg *arg, t_cmd *cmd)
{
	if (arg->cmd_list == cmd)
		ft_pipe_first_cmd(arg, cmd);
	else if (!cmd->next)
		ft_pipe_last_cmd(arg, cmd);
	else
		ft_pipe_middle_cmd(arg, cmd);
}

void	exit_fork(t_arg *arg, int exit_code)
{
	free(arg->prompt);
	free(arg->pwd);
	free(arg->whole_line);
	free_tab(arg->envp);
	free_tab(arg->paths);
	free_lst(arg->lexing);
	free_cmd_lst(arg->cmd_list);
	rl_clear_history();
	exit(exit_code);
}

void	exec_cmd(t_arg *arg, t_cmd *cmd)
{
	cmd->pid_child = fork();
	if (cmd->pid_child == 0)
	{
		dup2(arg->cmd_read_fd, STDIN_FILENO);
		close(arg->cmd_read_fd);
		dup2(arg->pipe_fd[1], STDOUT_FILENO);
		close(arg->pipe_fd[1]);
		close(arg->pipe_fd[0]);
		if (cmd->cmd_path)
			execve(cmd->cmd_path, cmd->argv, arg->envp);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		if (!cmd->cmd_path)
		{
			ft_putstr_fd(" : command not found\n", STDERR_FILENO);
			exit_fork(arg, 127);
		}
		ft_putstr_fd(" : execution KO\n", STDERR_FILENO);
		exit_fork(arg, 126);
	}
}

void	wait_childs(t_arg *arg, t_cmd *cmd)
{
	while (cmd)
	{
		if (!ft_isbuiltin(cmd))
		{
			waitpid(cmd->pid_child, &cmd->status, 0);
			if (cmd->cmd_path)
				arg->exit_code = WEXITSTATUS(cmd->status);
		}
		cmd = cmd->next;
	}
}

void	handle_multi_cmd(t_arg *arg, t_cmd *cmd)
{
	bool	redir_ok;

	while (cmd)
	{
		redir_ok = handle_redir(cmd);
		ft_pipe(arg, cmd);
		if (redir_ok)
		{
			// dprintf(2, "box_fd = %d\tpipe_fd[1] = %d\tpipe_fd[0] = %d\n",
			// 	arg->cmd_read_fd, arg->pipe_fd[1], arg->pipe_fd[0]);
			cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
			if (ft_isbuiltin(cmd))
			{
				if (cmd->output_fd == STDOUT_FILENO)
					handle_builtins(arg, cmd, arg->pipe_fd[1]);
				else
					handle_builtins(arg, cmd, cmd->output_fd);
			}
			else
				exec_cmd(arg, cmd);
		}
		else
			arg->exit_code = GENERAL_ERR;
		cmd = cmd->next;
	}
	close(arg->cmd_read_fd);
	close(arg->pipe_fd[0]);
	close(arg->pipe_fd[1]);
	wait_childs(arg, arg->cmd_list);
}
