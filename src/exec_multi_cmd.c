/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/08 15:54:05 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fork(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->pid_child = fork();
		cmd = cmd->next;
	}
}

void	ft_pipe(t_arg *arg, t_cmd *cmd, int pipe_fd[arg->nb_cmd][2], int cmd_no)
{
	if (cmd_no == 0)
	{
		pipe()
	}
	else if (cmd_no == arg->nb_cmd - 1)
	{

	}
	else
	{

	}
}

void	handle_multi_cmd(t_arg *arg, t_cmd *cmd)
{
	int	pipe_fd[arg->nb_cmd][2];
	int	cmd_no;

	ft_fork(arg->cmd_list);
	cmd_no = 0;
	while (cmd_no < arg->nb_cmd)
	{
		ft_pipe(arg, cmd, cmd_no);
	}
}

// void	ft_pipe(t_arg *arg, t_cmd *cmd, int cmd_no)
// {
// 	if (cmd_no == 0)
// 	{
// 		pipe(arg->pipe_fd[0]);
// 		arg->pipe_fd[1][0] = dup(cmd->input_fd);
// 		return ;
// 	}
// 	if (cmd_no == arg->nb_cmd - 1)
// 	{
// 		close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
// 		close(arg->pipe_fd[cmd_no % 2][0]);
// 		arg->pipe_fd[cmd_no % 2][1] = dup(cmd->output_fd);
// 		return ;
// 	}
// 	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
// 	close(arg->pipe_fd[cmd_no % 2][0]);
// 	pipe(arg->pipe_fd[cmd_no % 2]);
// }

// void	exec_cmd(t_arg *arg, t_cmd *cmd, int cmd_no)
// {
// 	cmd->pid_child = fork();
// 	if (cmd->pid_child == 0)
// 	{
// 		dup2(arg->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
// 		close(arg->pipe_fd[(cmd_no + 1) % 2][0]);
// 		dup2(arg->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
// 		close(arg->pipe_fd[cmd_no % 2][1]);
// 		close(arg->pipe_fd[cmd_no % 2][0]);
// 		if (cmd->cmd_path)
// 			execve(cmd->cmd_path, cmd->argv, arg->envp);
// 	}
// }

// void	wait_childs(t_arg *arg, t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		waitpid(cmd->pid_child, &cmd->status, 0);
// 		if (WEXITSTATUS(cmd->status) != 0)
// 			arg->exit_code = WEXITSTATUS(cmd->status);
// 		cmd = cmd->next;
// 	}
// }

// void	handle_multiple_cmd(t_arg *arg, t_cmd *cmd)
// {
// 	int		cmd_no;

// 	cmd_no = 0;
// 	while (cmd_no < arg->nb_cmd)
// 	{
// 		cmd->input_fd = handle_redir_input(cmd);
// 		cmd->output_fd = handle_redir_output(cmd);
// 		if (cmd->input_fd == -1 || cmd->output_fd == -1)
// 		{
// 			ft_pipe(arg, cmd, cmd_no);
// 			cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
// 			exec_cmd(arg, cmd, cmd_no);
// 		}
// 		cmd = cmd->next;
// 		cmd_no++;
// 	}
// 	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
// 	close(arg->pipe_fd[cmd_no % 2][0]);
// 	wait_childs(arg, arg->cmd_list);
// }
