/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:37:40 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/15 14:02:40 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: ft_pipe_first_cmd
 * ---------------------------
 * Sets up the pipe for the first command in the pipeline.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
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

/*
 * Function: ft_pipe_last_cmd
 * --------------------------
 * Sets up the pipe for the last command in the pipeline.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	ft_pipe_last_cmd(t_arg *arg, t_cmd *cmd)
{
	close(arg->cmd_read_fd);
	if (cmd->input_fd != STDIN_FILENO)
	{
		close(arg->pipe_fd[0]);
		arg->cmd_read_fd = cmd->input_fd;
	}
	else
		arg->cmd_read_fd = arg->pipe_fd[0];
	close(arg->pipe_fd[1]);
	if (cmd->output_fd != STDOUT_FILENO)
		arg->pipe_fd[1] = cmd->output_fd;
	else
		arg->pipe_fd[1] = dup(STDOUT_FILENO);
}

/*
 * Function: ft_pipe_middle_cmd
 * ----------------------------
 * Sets up the pipe for a command that is neither the first nor the last
 * in the pipeline.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	ft_pipe_middle_cmd(t_arg *arg, t_cmd *cmd)
{
	close(arg->cmd_read_fd);
	if (cmd->input_fd != STDIN_FILENO)
	{
		close(arg->pipe_fd[0]);
		arg->cmd_read_fd = cmd->input_fd;
	}
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

/*
 * Function: ft_pipe
 * ------------------
 * Sets up the pipe for command execution based on its position in the pipeline.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	ft_pipe(t_arg *arg, t_cmd *cmd)
{
	if (arg->cmd_list == cmd)
		ft_pipe_first_cmd(arg, cmd);
	else if (!cmd->next)
		ft_pipe_last_cmd(arg, cmd);
	else
		ft_pipe_middle_cmd(arg, cmd);
}
