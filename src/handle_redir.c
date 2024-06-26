/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:28:54 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/15 11:00:01 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: open_hd
 * ------------------
 * Opens a file descriptor for here-document mode.
 *
 * cmd: The command structure.
 * i: The index of the input file.
 *
 * Returns: The file descriptor of the opened file.
 */
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
	if (g_signal)
	{
		free(tmp_file_name);
		return (-1);
	}
	tmp_fd = open(tmp_file_name, O_RDONLY);
	unlink(tmp_file_name);
	free(tmp_file_name);
	return (tmp_fd);
}

/*
 * Function: invalid_fd
 * ---------------------
 * Handles invalid file descriptors.
 *
 * file_name: The name of the file.
 * here_doc: Flag indicating here-document mode.
 *
 * Returns: -1.
 */
int	invalid_fd(char *file_name, int here_doc)
{
	if (here_doc == 2 && !g_signal)
		perror("here_doc");
	else if (!g_signal)
		perror(file_name);
	return (-1);
}

/*
 * Function: handle_redir_input
 * -----------------------------
 * Handles input redirection for a command.
 *
 * cmd: The command structure.
 *
 * Returns: The file descriptor for input redirection.
 */
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
			return (invalid_fd(cmd->input_file[i], cmd->input_redir[i]));
		final_fd = tmp_fd;
		i++;
	}
	return (final_fd);
}

/*
 * Function: handle_redir_output
 * ------------------------------
 * Handles output redirection for a command.
 *
 * cmd: The command structure.
 *
 * Returns: The file descriptor for output redirection.
 */
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

/*
 * Function: handle_redir
 * -----------------------
 * Handles input and output redirection for a command.
 *
 * cmd: The command structure.
 *
 * Returns: True if redirection is successful, otherwise false.
 */
void	handle_redir(t_cmd *cmd)
{
	cmd->input_fd = handle_redir_input(cmd);
	cmd->output_fd = handle_redir_output(cmd);
	if (cmd->output_fd == -1 && cmd->input_fd != -1
		&& cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->input_fd == -1 && cmd->output_fd != -1
		&& cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}
