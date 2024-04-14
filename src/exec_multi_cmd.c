/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:44:32 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/14 16:32:58 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	found_path_line(char *str)
{
	if (!str || !(*str) || ft_strlen(str) < 5)
		return (false);
	if (*str == 'P' && *(str + 1) == 'A' && *(str + 2) == 'T'
		&& *(str + 3) == 'H' && *(str + 4) == '=')
		return (true);
	return (false);
}

char	**found_path(char **envp)
{
	while (envp && *envp && !found_path_line(*envp))
		envp++;
	if (!envp || !(*envp))
		return (NULL);
	return (ft_split(*envp + 5, ':'));
}

// /*
//  * Function: exec_builtins
//  * -----------------------
//  * Executes the built-in commands.
//  *
//  * arg: Pointer to the argument structure.
//  * cmd: Pointer to the command structure.
//  */
// void	exec_builtins(t_arg *arg, t_cmd *cmd)
// {
// 	if (cmd->output_fd == STDOUT_FILENO)
// 		handle_builtins(arg, cmd, arg->pipe_fd[1]);
// 	else
// 	{
// 		handle_builtins(arg, cmd, cmd->output_fd);
// 		close(cmd->output_fd);
// 	}
// 	dprintf(2, "hello there ! %s\n", cmd->argv[0]);
// }

/*
 * Function: exec_cmd
 * -------------------
 * Executes a command.
 *
 * arg: Pointer to the argument structure.
 * cmd: Pointer to the command structure.
 */
void	exec_cmd(t_arg *arg, t_cmd *cmd)
{
	cmd->pid_child = fork();
	if (cmd->pid_child == 0)
	{
		dup2(arg->cmd_read_fd, STDIN_FILENO);
		close(arg->cmd_read_fd);
		dup2(arg->pipe_fd[1], STDOUT_FILENO);
		close(arg->pipe_fd[1]);
		close(arg->pipe_fd[0]);
		if (ft_isbuiltin(cmd))
		{
			handle_builtins(arg, cmd, STDOUT_FILENO);
			exit_fork(arg, arg->exit_code);
		}
		if (cmd->cmd_path && access(cmd->cmd_path, X_OK) == 0)
			execve(cmd->cmd_path, cmd->argv, arg->envp);
		exec_errors(arg, cmd);
	}
}

/*
 * Function: wait_childs
 * ----------------------
 * Waits for child processes to terminate.
 *
 * arg:     Pointer to the argument structure.
 * cmd:     Pointer to the command structure.
 * nb_cmd:  Number of commands to wait for.
 */
void	wait_childs(t_arg *arg, t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd->input_fd != -1 && cmd->output_fd != -1)
		{
			waitpid(cmd->pid_child, &cmd->status, 0);
			if (cmd->cmd_path && access(cmd->cmd_path, X_OK) == 0)
				arg->exit_code = WEXITSTATUS(cmd->status);
		}
		cmd = cmd->next;
		i++;
	}
}

/*
 * Function: handle_multi_cmd
 * ---------------------------
 * Handles execution of multiple commands in a pipeline.
 *
 * arg:     Pointer to the argument structure.
 * cmd:     Pointer to the command structure.
 */
void	handle_multi_cmd(t_arg *arg, t_cmd *cmd)
{
	bool	redir_ok;
	int		nb_cmd;

	nb_cmd = 0;
	while (cmd && g_here_doc_fd != -1)
	{
		redir_ok = handle_redir(cmd);
		ft_pipe(arg, cmd);
		if (redir_ok)
		{
			if (!ft_isbuiltin(cmd))
			{
				arg->paths = found_path(arg->envp);
				cmd->cmd_path = ft_which(arg->paths, cmd->argv[0]);
				free_tab(arg->paths);
			}
			exec_cmd(arg, cmd);
		}
		else
			arg->exit_code = GENERAL_ERR;
		cmd = cmd->next;
		nb_cmd++;
	}
	close(arg->cmd_read_fd);
	close(arg->pipe_fd[0]);
	close(arg->pipe_fd[1]);
	wait_childs(arg, arg->cmd_list, nb_cmd);
}
