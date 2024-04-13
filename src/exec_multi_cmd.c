/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/13 12:06:27 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtins(t_arg *arg, t_cmd *cmd)
{
	if (cmd->output_fd == STDOUT_FILENO)
		handle_builtins(arg, cmd, arg->pipe_fd[1]);
	else
		handle_builtins(arg, cmd, cmd->output_fd);
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
		if (cmd->cmd_path && access(cmd->cmd_path, X_OK) == 0)
			execve(cmd->cmd_path, cmd->argv, arg->envp);
		exec_errors(arg, cmd);
	}
}

void	wait_childs(t_arg *arg, t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (!ft_isbuiltin(cmd) && cmd->input_fd != -1 && cmd->output_fd != -1)
		{
			waitpid(cmd->pid_child, &cmd->status, 0);
			if (cmd->cmd_path && access(cmd->cmd_path, X_OK) == 0)
				arg->exit_code = WEXITSTATUS(cmd->status);
		}
		cmd = cmd->next;
		i++;
	}
}

void	handle_multi_cmd(t_arg *arg, t_cmd *cmd)
{
	bool	redir_ok;
	int		nb_cmd;

	nb_cmd = 0;
	while (cmd && g_here_doc_fd != -1)
	{
		redir_ok = handle_redir(cmd);
		ft_pipe(arg, cmd);
		if (redir_ok)
		{
			cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
			if (ft_isbuiltin(cmd))
				exec_builtins(arg, cmd);
			else
				exec_cmd(arg, cmd);
		}
		else
			arg->exit_code = GENERAL_ERR;
		cmd = cmd->next;
		nb_cmd++;
	}
	close(arg->cmd_read_fd);
	close(arg->pipe_fd[0]);
	close(arg->pipe_fd[1]);
	wait_childs(arg, arg->cmd_list, nb_cmd);
}
