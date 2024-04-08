/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:28:54 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/08 15:26:33 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_redir_input(t_cmd *cmd)
{
	int	i;

	if (!cmd->input_file)
		return (0);
	i = 0;
	while (cmd->input_file[i])
		i++;
	return (i);
}

int nb_redir_output(t_cmd *cmd)
{
	int	i;

	if (!cmd->output_file)
		return (0);
	i = 0;
	while (cmd->output_file[i])
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
	char	*tmp_file_name_i;
	int		tmp_fd;
	char	*lim_lr;

	tmp_file_name_i = ft_itoa(i);
	tmp_file_name = ft_strjoin(TMP_FILE, tmp_file_name_i);
	free(tmp_file_name_i);
	tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp_fd == -1)
		return (tmp_fd);
	lim_lr = ft_strjoin(cmd->input_file[i], "\n");
	read_input(tmp_fd, lim_lr);
	close(tmp_fd);
	free(lim_lr);
	tmp_fd = open(tmp_file_name, O_RDONLY);
	unlink(tmp_file_name);
	free(tmp_file_name);
	return (tmp_fd);
}

int	invalid_fd(char *file_name, int here_doc)
{
	if (here_doc == 2)
		perror("here_doc");
	else
		perror(file_name);
	return (-1);
}

int	handle_redir_input(t_cmd *cmd)
{
	int	nb_redir;
	int	tmp_fd;
	int	final_fd;
	int	i;

	if (!cmd->input_redir[0])
		return (STDIN_FILENO);
	nb_redir = nb_redir_input(cmd);
	i = 0;
	while (i < nb_redir)
	{
		if (cmd->input_redir[i] == 1)
			tmp_fd = open(cmd->input_file[i], O_RDONLY);
		else if (cmd->input_redir[i] == 2)
			tmp_fd = open_hd(cmd, i);
		if (i != 0)
			close(final_fd);
		if (tmp_fd == -1)
			return (invalid_fd(cmd->input_file[i], cmd->input_redir[i] == 1));
		final_fd = tmp_fd;
		i++;
	}
	return (final_fd);
}

int	handle_redir_output(t_cmd *cmd)
{
	int	nb_redir;
	int	tmp_fd;
	int	final_fd;
	int	i;

	if (!cmd->output_redir[0])
		return (STDOUT_FILENO);
	nb_redir = nb_redir_output(cmd);
	i = 0;
	while (i < nb_redir)
	{
		if (cmd->output_redir[i] == 1)
			tmp_fd = open(cmd->output_file[i], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
		else if (cmd->output_redir[i] == 2)
			tmp_fd = open(cmd->output_file[i], O_WRONLY | O_CREAT | O_APPEND,
				0777);
		if (i != 0)
			close(final_fd);
		if (tmp_fd == -1)
			return (invalid_fd(cmd->output_file[i], 0));
		final_fd = tmp_fd;
		i++;
	}
	return (final_fd);
}
