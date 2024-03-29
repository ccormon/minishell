/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/29 11:51:17 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(t_arg *arg, int cmd_no)
{

}

void	exec_cmd(t_arg *arg, int cmd_no, char **envp)
{

}

void	wait_childs(t_arg *arg)
{

}

int	handle_multiple_cmd(t_arg *param, char **envp)
{
	t_arg	*arg;
	int		cmd_no;

	arg = param;
	cmd_no = 0;
	while (arg->cmd_list->next)
	{
		ft_pipe(arg, cmd_no);
		exec_cmd(arg, cmd_no, envp);
		arg->cmd_list = arg->cmd_list->next;
	}
	close(arg->pipe_fd[(cmd_no + 1) % 2][1]);
	close(arg->pipe_fd[cmd_no % 2][0]);
	wait_childs(param);
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
