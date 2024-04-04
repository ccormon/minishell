/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:52:15 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/04 11:38:21 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: handle_signal
 * ------------------------
 * Signal handler function to handle SIGINT (Ctrl+C) signal. This function is
 * typically invoked when the user interrupts the program by pressing Ctrl+C.
 *
 * sig: The signal number received by the handler.
 */
static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}
/*struct sigaction	sig;
*
*sig.sa_handler = &handle_signal;
*sigaction(SIGINT, &sig, NULL);
*sigaction(SIGQUIT, SIG_IGN, NULL);
*/

/*
 * Function: init_paths
 * ---------------------
 * Initializes the paths for executable files by extracting the PATH environment
 * variable.
 *
 * arg:   Pointer to a structure containing command arguments and settings.
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

//is it good for export ??
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

static int	fetch_line(char **envp)
{
	t_arg	arg;

	arg.whole_line = NULL;
	arg.paths = NULL;
	arg.envp = ft_tabdup(envp);
	arg.prompt = get_prompt(arg.envp);
	init_paths(&arg, arg.envp);
	while (1)
	{
		arg.lexing = NULL;
		arg.exit_code = 0;
		arg.whole_line = readline(arg.prompt);
		add_history(arg.whole_line);
		if (!arg.whole_line)
		{
			printf("test\n");
			write(1, "exit\n", 5);
			break ;
		}
		// parse_line(&arg);
		// printf("exit code = %d\n", arg.exit_code);
		if (parse_line(&arg))
			executing(&arg);
		free(arg.whole_line);
		free_lst(arg.lexing);
		free_cmd_lst(arg.cmd_list);
	}
	ft_exit(&arg);
	return (arg.exit_code);
}

/*
 * Function: main
 * ---------------
 * Entry point of the program. This function initializes the minishell,
 * sets up signal handling for SIGINT and SIGQUIT, and then enters
 * the main loop to fetch and process user input.
 *
 * argc: Number of command-line arguments passed to the program.
 * argv: Array of strings containing the command-line arguments.
 * envp: Array of strings containing the environment variables.
 *
 * returns: The exit status of the program.
 */
int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Minishell cannot take arguments\n", 2);
		return (EXIT_FAILURE);
	}
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (fetch_line(envp));
}
