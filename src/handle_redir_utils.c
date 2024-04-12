/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:45 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/12 18:31:30 by ccormon          ###   ########.fr       */
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

void	read_input(int tmp_fd, char *lim_lr)
{
	char	*buffer;

	g_here_doc_fd = dup(STDIN_FILENO);
	ft_putstr_fd("> ", STDOUT_FILENO);
	signal(SIGINT, &handle_signal_hd);
	buffer = get_next_line(g_here_doc_fd);
	while (buffer && !ft_strcmp(buffer, lim_lr))
	{
		ft_putstr_fd(buffer, tmp_fd);
		free(buffer);
		ft_putstr_fd("> ", STDOUT_FILENO);
		buffer = get_next_line(g_here_doc_fd);
	}
	if (buffer)
		free(buffer);
	else if (g_here_doc_fd != -1)
		ft_putstr_fd("warning : here-document delimited by end-of-file\n",
				STDERR_FILENO);
	signal(SIGINT, &handle_signal_cmd);
	close(g_here_doc_fd);
}
