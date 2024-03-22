/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/22 18:38:34 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

int	ft_execve(t_arg *arg, char **envp)
{
	pid_t	child;
	int		status;
	size_t	i;

	if (!arg->cmd_list)
		return ;
	child = fork();
	if (child == 0)
	{
		i = 0;
		while (arg->paths[i])
		{
			arg->cmd_list->cmd_path = ft_strjoin_path(arg->paths[i++],
				arg->cmd_list->cmd_name);
			execve(arg->cmd_list->cmd_path, arg->cmd_list->argument, envp);
			free(arg->cmd_list->cmd_path);
		}
		arg->cmd_list->cmd_path = NULL;
		perror("access");
		ft_exit(INVALID_CMD); // a definir
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

void	executing(t_arg *param, char **envp)
{
	t_arg	*arg;
	size_t	cmd_no;

	arg = param;
	if (!arg->cmd_list->next)
	{
		arg->exit_code = ft_execve(arg, envp);
		return ;
	}
	cmd_no = 0;
	while (arg->cmd_list->next)
	{

	}
}

// void	ft_pipe(t_pipex *data, size_t cmd_no)
// {
// 	if (cmd_no == 0)
// 	{
// 		pipe(data->pipe_fd[0]);
// 		data->pipe_fd[1][0] = dup(data->in_fd);
// 		return ;
// 	}
// 	if (cmd_no == data->nb_cmd - 1)
// 	{
// 		close(data->pipe_fd[(cmd_no + 1) % 2][1]);
// 		close(data->pipe_fd[cmd_no % 2][0]);
// 		data->pipe_fd[cmd_no % 2][1] = dup(data->out_fd);
// 		return ;
// 	}
// 	close(data->pipe_fd[(cmd_no + 1) % 2][1]);
// 	close(data->pipe_fd[cmd_no % 2][0]);
// 	pipe(data->pipe_fd[cmd_no % 2]);
// }

// void	exec_cmd(t_pipex *data, char **envp, size_t cmd_no)
// {
// 	data->pid_child[cmd_no] = fork();
// 	if (data->pid_child[cmd_no] == 0)
// 	{
// 		dup2(data->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
// 		close(data->pipe_fd[(cmd_no + 1) % 2][0]);
// 		dup2(data->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
// 		close(data->pipe_fd[cmd_no % 2][1]);
// 		close(data->pipe_fd[cmd_no % 2][0]);
// 		if (data->cmd[cmd_no].path)
// 			execve(data->cmd[cmd_no].path, data->cmd[cmd_no].args, envp);
// 		if (data->cmd[cmd_no].args)
// 			error_msg(data->cmd[cmd_no].args[0]);
// 		else
// 			ft_putstr_fd("invalid command\n", STDERR_FILENO);
// 		exit_pipex(data, 127);
// 	}
// }

// void	wait_childs(t_pipex *data)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < data->nb_cmd)
// 		waitpid(data->pid_child[i++], NULL, 0);
// }

// void	pipex(t_pipex *data, char **envp)
// {
// 	size_t	cmd_no;

// 	cmd_no = 0;
// 	while (cmd_no < data->nb_cmd)
// 	{
// 		ft_pipe(data, cmd_no);
// 		exec_cmd(data, envp, cmd_no);
// 		cmd_no++;
// 	}
// 	close(data->pipe_fd[(cmd_no + 1) % 2][1]);
// 	close(data->pipe_fd[cmd_no % 2][0]);
// 	wait_childs(data);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	data;

// 	if (argc < 5)
// 	{
// 		ft_putstr_fd("Wrong number of arguments.\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	data.here_doc = false;
// 	if (ft_strcmp(argv[1], "here_doc"))
// 		data.here_doc = true;
// 	if (data.here_doc && argc < 6)
// 	{
// 		ft_putstr_fd("Wrong number of arguments.\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	init_pipex(&data, argc - 1, argv + 1, envp);
// 	pipex(&data, envp);
// 	exit_pipex(&data, 0);
// 	return (EXIT_SUCCESS);
// }
