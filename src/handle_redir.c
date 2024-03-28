/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:28:54 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/28 17:30:05 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_redir(t_cmd *cmd)
{
	int	i;

	if (!cmd->input_file)
		return (0);
	i = 0;
	while (cmd->input_file[i])
		i++;
	return (i);
}

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

int	open_hd(t_cmd *cmd, int i)
{
	char	*tmp_file_name;
	int		tmp_fd;
	char	*lim_lr;

	tmp_file_name = ft_strjoin(TMP_FILE, i);
	tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp_fd == -1)
		return (tmp_fd);
	lim_lr = ft_strjoin(cmd->input_file[i], "\n");
	read_input(tmp_fd, lim_lr);
	close(tmp_fd);
	tmp_fd = open(tmp_file_name, O_RDONLY);
	unlink(tmp_file_name);
	free(tmp_file_name);
	return (tmp_fd);
}

int	handle_redir_input(t_cmd *cmd)
{
	int	*tmp_fd;
	int	final_fd;
	int	i;

	tmp_fd = malloc(nb_redir(cmd) * sizeof(int));
	i = -1;
	while (cmd->input_redir[++i])
	{
		if (cmd->input_redir[i] == 1)
			tmp_fd[i] = open(cmd->input_file[i], O_RDONLY);
		else if (cmd->input_redir[i] == 2)
			tmp_fd[i] = open_hd(cmd, i);
	}
	final_fd = tmp_fd[0];
	i = 1;
	while (cmd->input_redir[i + 1])
	{
		if (tmp_fd[i] == -1)
			final_fd = tmp_fd[i];
		close(tmp_fd[i++]);
	}
	if (final_fd != -1)
		final_fd = tmp_fd[i];
	free(tmp_fd);
	return (final_fd);
}

int	handle_redir_output(t_cmd *cmd)
{
	int	*tmp_fd;
	int final_fd;
	int	i;

	tmp_fd = malloc(nb_redir(cmd) * sizeof(int));
	i = -1;
	while (cmd->output_redir[++i])
	{
		if (cmd->output_redir[i] == 1)
			tmp_fd[i] = open(cmd->output_file[i], O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
		else if (cmd->output_redir[i] == 2)
			tmp_fd[i] = open(cmd->output_file[i], O_WRONLY | O_CREAT
				| O_APPEND, 0777);
	}
	final_fd = tmp_fd[0];
	i = 1;
	while (cmd->input_redir[i + 1])
	{
		if (tmp_fd[i] == -1)
			final_fd = tmp_fd[i];
		close(tmp_fd[i++]);
	}
	if (final_fd != -1)
		final_fd = tmp_fd[i];
	free(tmp_fd);
	return (final_fd);
}
