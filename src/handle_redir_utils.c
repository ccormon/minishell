/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:45 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/15 11:07:19 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: nb_redir_input
 * -------------------------
 * Counts the number of input redirections in a command.
 *
 * cmd: Pointer to the command structure.
 *
 * Returns: The number of input redirections.
 */
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

/*
 * Function: nb_redir_output
 * --------------------------
 * Counts the number of output redirections in a command.
 *
 * cmd: Pointer to the command structure.
 *
 * Returns: The number of output redirections.
 */
int	nb_redir_output(t_cmd *cmd)
{
	int	i;

	if (!cmd->output_file)
		return (0);
	i = 0;
	while (cmd->output_file[i])
		i++;
	return (i);
}

/*
 * Function: read_input
 * ---------------------
 * Reads input for here-document redirection.
 *
 * tmp_fd: Temporary file descriptor for writing input.
 * lim_lr: Delimiter for here-document.
 */
void	read_input(int tmp_fd, char *lim_lr)
{
	char	*buffer;

	ft_putstr_fd("> ", STDOUT_FILENO);
	change_signal(2);
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
	else if (!g_signal)
		ft_putstr_fd("warning : here-document delimited by end-of-file\n",
			STDERR_FILENO);
	change_signal(0);
}
