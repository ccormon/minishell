/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:25:31 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/09 18:59:15 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_one_cmd(t_arg *arg)
{
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
	arg->exit_code = WEXITSTATUS(arg->cmd_list->status);
}

void	handle_one_cmd(t_arg *arg)
{
	if (!handle_redir(arg->cmd_list))
	{
		arg->exit_code = GENERAL_ERR;
		return ;
	}
	if (handle_builtins(arg, arg->cmd_list))
		return ;
	arg->cmd_list->cmd_path = ft_which(arg->paths,
			arg->cmd_list->argv[0]);
	if (!arg->cmd_list->cmd_path)
	{
		arg->exit_code = INVALID_CMD;
		ft_putstr_fd(arg->cmd_list->argv[0], STDERR_FILENO);
		ft_putstr_fd(" : command not found\n", STDERR_FILENO);
		return ;
	}
	exec_one_cmd(arg);
}
