/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:35:39 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:38:51 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: init_paths
 * ---------------------
 * Initializes the paths for executable files by extracting the PATH environment
 * variable.
 *
 * arg:   Pointer to a structure containing command argv and settings.
 * envp:  Array of strings containing the environment variables.
 */
static void	init_paths(t_arg *arg, char **envp)
{
	char	*path_line;

	path_line = find_str(envp, "PATH=", 5);
	if (!path_line)
	{
		arg->paths = NULL;
		return ;
	}
	arg->paths = ft_split(path_line, ':');
}

/*
 * Function: ft_tabdup
 * --------------------
 * Duplicates a null-terminated array of strings.
 *
 * src: The array of strings to be duplicated.
 *
 * Returns: A pointer to the duplicated array of strings.
 */
static char	**ft_tabdup(char **src)
{
	int		i;
	char	**dest;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

/*
 * Function: init_arg
 * -------------------
 * Initializes the argument structure with environment variables 
 * and other settings.
 *
 * arg:   Pointer to the argument structure to be initialized.
 * envp:  The environment variables array.
 */
static void	init_arg(t_arg *arg, char **envp)
{
	arg->whole_line = NULL;
	arg->paths = NULL;
	arg->exit_code = 0;
	arg->nb_cmd = 0;
	arg->envp = ft_tabdup(envp);
	arg->pwd = getcwd(NULL, 0);
	arg->prompt = get_prompt(arg->envp);
	init_paths(arg, arg->envp);
	if (!find_str(envp, "PWD=", 4))
		rewrite_evar(arg, "PWD=", getcwd(NULL, 0));
}

/*
 * Function: fetch_line
 * ---------------------
 * Fetches input lines from the user, parses them, executes the commands,
 * and handles the shell loop.
 *
 * envp: The environment variables array.
 *
 * Returns: The exit code of the shell.
 */
int	fetch_line(char **envp)
{
	t_arg	arg;

	init_arg(&arg, envp);
	while (1)
	{
		arg.lexing = NULL;
		arg.whole_line = readline(arg.prompt);
		add_history(arg.whole_line);
		if (!arg.whole_line)
			break ;
		if (parse_line(&arg))
		{
			executing(&arg);
			free_lst(arg.lexing);
			free_cmd_lst(arg.cmd_list);
		}
		free(arg.whole_line);
	}
	builtin_exit(&arg, NULL, false);
	return (arg.exit_code);
}
