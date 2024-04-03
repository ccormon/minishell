/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:25:31 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/03 10:28:02 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	exec_one_cmd(t_arg *arg, char **envp)
{
	// int	builtin_code;

	// builtin_code = isbuiltins(arg);
	// if (builtin_code != 0)
	// 	return (handle_builtins(arg, envp, builtin_code));
	arg->cmd_list->pid_child = fork();
	if (arg->cmd_list->pid_child == 0)
	{
		if (arg->cmd_list->input_redir)
		{
			dup2(arg->cmd_list->input_fd, STDIN_FILENO);
			close(arg->cmd_list->input_fd);
		}
		if (arg->cmd_list->output_redir)
		{
			dup2(arg->cmd_list->input_fd, STDOUT_FILENO);
			close(arg->cmd_list->output_fd);
		}
		execve(arg->cmd_list->cmd_path, arg->cmd_list->arguments, envp);
	}
	if (arg->cmd_list->input_redir)
		close(arg->cmd_list->input_fd);
	if (arg->cmd_list->output_redir)
		close(arg->cmd_list->output_fd);
	waitpid(arg->cmd_list->pid_child, &arg->cmd_list->status, 0);
	return (WEXITSTATUS(arg->cmd_list->status));
}

int	handle_one_cmd(t_arg *arg, char **envp)
{
	arg->cmd_list->cmd_path = ft_which(arg->paths,
		arg->cmd_list->arguments[0]);
	if (!arg->cmd_list->cmd_path)
		return (INVALID_CMD);
	if (arg->cmd_list->input_redir)
	{
		arg->cmd_list->input_fd = handle_redir_input(arg->cmd_list);
		if (arg->cmd_list->input_fd == -1)
			return (GENERAL_ERR);
	}
	else
		arg->cmd_list->input_fd = STDIN_FILENO;
	if (arg->cmd_list->output_redir)
	{
		arg->cmd_list->output_fd = handle_redir_output(arg->cmd_list);
		if (arg->cmd_list->output_fd == -1)
			return (GENERAL_ERR);
	}
	else
		arg->cmd_list->output_fd = STDOUT_FILENO;
	return (exec_one_cmd(arg, envp));
}
