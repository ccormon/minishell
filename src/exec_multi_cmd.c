/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/09 20:12:40 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(t_arg *arg, t_cmd *cmd, bool redir_ok, int cmd_no)
{
	if (cmd_no == 0)
	{
		pipe(arg->pipe_fd[0]);
		if (redir_ok && cmd->input_fd != STDIN_FILENO)
			arg->pipe_fd[1][0] = cmd->input_fd;
		else if (redir_ok)
			arg->pipe_fd[1][0] = dup(STDIN_FILENO);
		return ;
	}
	if (cmd_no == arg->nb_cmd - 1)
	{
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
		if (redir_ok && cmd->output_fd != STDOUT_FILENO)
			arg->pipe_fd[cmd_no % 2][1] = cmd->output_fd;
		else if (redir_ok)
			arg->pipe_fd[cmd_no % 2][1] = dup(STDOUT_FILENO);
		return ;
	}
	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	pipe(arg->pipe_fd[cmd_no % 2]);
}

void	exec_cmd(t_arg *arg, t_cmd *cmd, bool redir_ok, int cmd_no)
{
	cmd->pid_child = fork();
	if (cmd->pid_child == 0 && redir_ok)
	{
		dup2(arg->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
		// if (cmd->input_fd != STDIN_FILENO)
		close(arg->pipe_fd[(cmd_no + 1) % 2][0]);
		dup2(arg->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
		// if (cmd->output_fd != STDOUT_FILENO)
		close(arg->pipe_fd[cmd_no % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
		if (cmd->cmd_path)
			execve(cmd->cmd_path, cmd->argv, arg->envp);
		exit(GENERAL_ERR);
	}
	else if (cmd->pid_child == 0 && !redir_ok)
		exit(GENERAL_ERR);
}

void	wait_childs(t_arg *arg, t_cmd *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid_child, &cmd->status, 0);
		if (WEXITSTATUS(cmd->status) != 0)
			arg->exit_code = WEXITSTATUS(cmd->status);
		cmd = cmd->next;
	}
}

void	handle_multiple_cmd(t_arg *arg, t_cmd *cmd)
{
	t_cmd	*tmp;
	bool	redir_ok;
	int		cmd_no;

	cmd_no = 0;
	while (cmd_no < arg->nb_cmd)
	{
		redir_ok = handle_redir(cmd); //what if there is an error in the redirs, you do the next step ?
		ft_pipe(arg, cmd, redir_ok, cmd_no);
		cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
		exec_cmd(arg, cmd, redir_ok, cmd_no);
		tmp = cmd;
		cmd = cmd->next;
		cmd_no++;
	}
	if (redir_ok && tmp->output_fd != STDOUT_FILENO)
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	wait_childs(arg, cmd);
}
