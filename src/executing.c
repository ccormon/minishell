/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/25 17:38:19 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(t_arg *arg)
{
	int		tmp_fd;
	size_t	i;

	if (!arg->cmd_list->input_file || !arg->cmd_list->input_file[0])
		return (-1);
	i = 0;
	while (arg->cmd_list->input_file[i + 1])
	{
		tmp_fd = open(arg->cmd_list->input_file[i++], O_RDONLY);
		if (tmp_fd == -1)
			return (-1);
		close(tmp_fd);
	}
	return (open(arg->cmd_list->input_file[i], O_RDONLY));
}

int	open_infile_hd(t_arg *arg)
{

}

bool	handle_redir(t_arg *arg)
{
	if (arg->cmd_list->input_redir == 1 || arg->cmd_list->input_redir == 2)
	{
		if (arg->cmd_list->input_redir == 1)
			arg->cmd_list->input_fd = open_infile(arg);
		else if (arg->cmd_list->input_redir == 2)
			arg->cmd_list->input_fd = open_infile_hd(arg);
		if (arg->cmd_list->input_fd == -1)
			return (false);
		dup2(arg->cmd_list->input_fd, STDIN_FILENO);
		close(arg->cmd_list->input_fd);
	}
	if (arg->cmd_list->output_redir == 1 || arg->cmd_list->output_redir == 2)
	{
		arg->cmd_list->output_fd = open_outfile(arg);
		if (arg->cmd_list->output_fd == -1)
			return (false);
		dup2(arg->cmd_list->output_redir, STDOUT_FILENO);
		close(arg->cmd_list->output_redir);
	}
	return (true);
}

int	exec_one_code(t_arg *arg, char **envp)
{
	arg->cmd_list->cmd_path = ft_which(arg->cmd_list->cmd_name, arg->paths);
	if (!arg->cmd_list->cmd_path)
		return (INVALID_CMD);
	if (!handle_redir(arg))
		return (GENERAL_ERR);
	return (0);
}

void	executing(t_arg *arg, char **envp)
{
	if (!arg->cmd_list->next)
	{
		// execute one command
		arg->exit_code = exec_one_cmd(arg, envp);
	}
	else
	{
		// execute multiple command
	}
}
