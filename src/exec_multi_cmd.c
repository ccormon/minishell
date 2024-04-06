/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/06 17:28:41 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	handle_redir_multi_cmd(t_arg *arg, t_cmd *cmd, int cmd_no)
{
	if (cmd->input_redir[0])
	{
		cmd->input_fd = handle_redir_input(cmd);
		if (cmd->input_fd == -1)
			return (false);
		arg->pipe_fd[(cmd_no + 1) % 2][0] = dup(cmd->input_fd);
	}
	else if (cmd_no == 0)
		arg->pipe_fd[(cmd_no + 1) % 2][0] = dup(STDIN_FILENO);
	if (cmd->output_redir[0])
	{
		cmd->output_fd = handle_redir_output(cmd);
		if (cmd->output_fd == -1)
			return (false);
		arg->pipe_fd[cmd_no % 2][1] = dup(cmd->output_fd);
	}
	else if (cmd_no + 1 == arg->nb_cmd)
		arg->pipe_fd[cmd_no % 2][1] = dup(STDOUT_FILENO);
	return (true);
}

bool	ft_pipe(t_arg *arg, t_cmd *cmd, int cmd_no)
{
	if (cmd_no == 0)
	{
		pipe(arg->pipe_fd[cmd_no % 2]);
		return (handle_redir_multi_cmd(arg, cmd, cmd_no));
	}
	if (cmd_no + 1 == arg->nb_cmd)
	{
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
		return (handle_redir_multi_cmd(arg, cmd, cmd_no));
	}
	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	pipe(arg->pipe_fd[cmd_no % 2]);
	return (handle_redir_multi_cmd(arg, cmd, cmd_no));
}

// dup2(STDIN, STDIN) ne fait rien !
void	exec_cmd(t_arg *arg, t_cmd *cmd, int cmd_no)
{
	cmd->pid_child = fork();
	if (cmd->pid_child == 0)
	{
		dup2(arg->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
		close(arg->pipe_fd[(cmd_no + 1) % 2][0]);
		dup2(arg->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
		close(arg->pipe_fd[cmd_no % 2][1]);
		close(arg->pipe_fd[cmd_no % 2][0]);
		execve(cmd->cmd_path, cmd->argv, arg->envp);
	}
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
	int		cmd_no;

	cmd_no = 0;
	while (cmd)
	{
		if (!ft_pipe(arg, cmd, cmd_no))
		{
			arg->exit_code = GENERAL_ERR;
			return ;
		}
		cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
		exec_cmd(arg, cmd, cmd_no);
		tmp = cmd;
		cmd = cmd->next;
	}
	if (tmp->output_file[0])
		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	wait_childs(arg, arg->cmd_list);
}
