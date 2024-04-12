/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:37:40 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/12 14:38:05 by ccormon          ###   ########.fr       */
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
