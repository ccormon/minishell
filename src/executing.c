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

void	read_input(int tmp_fd, char *lim_lr)
{
	char	*buffer;

	ft_putstr_fd("> ", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer && !ft_strcmp(buffer, lim_lr))
	{
		ft_putstr_fd(buffer, tmp_fd);
		free(buffer);
		ft_putstr_fd("> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	if (buffer)
		free(buffer);
}

int	open_hd(t_arg *arg, int i)
{
	char	*tmp_file_name;
	int		tmp_fd;
	char	*lim_lr;

	tmp_file_name = ft_strjoin(TMP_FILE, i);
	tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp_fd == -1)
		return (tmp_fd);
	lim_lr = ft_strjoin(arg->cmd_list->input_file[i], "\n");
	read_input(tmp_fd, lim_lr);
	close(tmp_fd);
	tmp_fd = open(tmp_file_name, O_RDONLY);
	unlink(tmp_file_name);
	free(tmp_file_name);
	return (tmp_fd);
}

int	handle_redir(t_arg *arg)
{
	int	*tmp_fd;
	int	final_fd;
	int	i;

	tmp_fd = malloc(ft_strlen(arg->cmd_list->input_redir) * sizeof(int));
	i = 0;
	while (arg->cmd_list->input_redir[i])
	{
		if (arg->cmd_list->input_redir[i] == 1)
			tmp_fd[i] = open(arg->cmd_list->input_file[i], O_RDONLY);
		else if (arg->cmd_list->input_redir[i] == 2)
			tmp_fd[i] = open_hd(arg, i);
		close(tmp_fd[i]);
		i++;
	}
	i = 0;
	while (arg->cmd_list->input_redir[i + 1])
	{
		if (tmp_fd[i] == -1)
			final_fd = tmp_fd[i];
		close(tmp_fd[i]);
		i++;
	}
	if (i == 0)
		final_fd = tmp_fd[0];
	else if (final_fd != -1)
		final_fd = tmp_fd[i];
	free(tmp_fd);
	return (final_fd);
}

int	exec_one_cmd(t_arg *arg, char **envp)
{
	arg->cmd_list->cmd_path = ft_which(arg->cmd_list->cmd_name, arg->paths);
	if (!arg->cmd_list->cmd_path)
		return (INVALID_CMD);
	if (arg->cmd_list->input_redir)
		if (handle_redir(arg) == -1)
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
