/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:05:57 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/14 13:39:35 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

/*
 * Function: ft_strjoin_path
 * --------------------------
 * Joins two strings, path and cmd, inserting a '/' character between them.
 *
 * path: The path string.
 * cmd: The command string.
 *
 * returns: The concatenated string.
 */
char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*cmd_path;
	size_t	i;

	cmd_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2 * sizeof(char));
	i = 0;
	while (*path)
		cmd_path[i++] = *path++;
	cmd_path[i++] = '/';
	while (*cmd)
		cmd_path[i++] = *cmd++;
	cmd_path[i] = '\0';
	return (cmd_path);
}

/*
 * Function: ft_which
 * -------------------
 * Locates the executable file corresponding to the given command.
 *
 * paths: Array of paths to search in.
 * cmd: The command to search for.
 *
 * returns: The full path to the executable file if found, otherwise NULL.
 */
char	*ft_which(char **paths, char *cmd)
{
	char	*cmd_path;
	size_t	i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_strjoin_path(paths[i++], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

/*
 * Function: nb_cmd
 * ----------------
 * Counts the number of commands in the linked list.
 *
 * cmd: Pointer to the head of the command linked list.
 *
 * returns: The number of commands.
 */
int	nb_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/*
 * Function: exit_fork
 * --------------------
 * Frees memory and exits the process with the specified exit code.
 *
 * arg: Pointer to the argument structure.
 * exit_code: The exit code to be returned.
 */
void	exit_fork(t_arg *arg, int exit_code)
{
	free(arg->prompt);
	free(arg->pwd);
	free(arg->whole_line);
	free_tab(arg->envp);
	free_tab(arg->paths);
	free_lst(arg->lexing);
	free_cmd_lst(arg->cmd_list);
	rl_clear_history();
	exit(exit_code);
}

/*
 * Function: exec_errors
 * ---------------------
 * Handles errors that occur during command execution.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	exec_errors(t_arg *arg, t_cmd *cmd)
{
	if (!cmd->argv[0] && (cmd->input_redir[0] || cmd->output_redir[0]))
		exit_fork(arg, EXIT_SUCCESS);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	if (cmd->cmd_path && access(cmd->cmd_path, X_OK) != 0)
	{
		perror(" ");
		exit_fork(arg, EXEC_CMD_KO);
	}
	if (!cmd->argv[0][0] || (!cmd->cmd_path && cmd->argv[0]))
	{
		if (ft_strchr(cmd->argv[0], '/'))
			perror(" ");
		else
			ft_putstr_fd(" : command not found\n", STDERR_FILENO);
		exit_fork(arg, INVALID_CMD);
	}
	if (cmd->argv[0])
	{
		ft_putstr_fd(" : Is a directory\n", STDERR_FILENO);
		exit_fork(arg, EXEC_CMD_KO);
	}
}
