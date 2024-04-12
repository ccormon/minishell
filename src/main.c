/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:52:15 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/12 18:40:15 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_here_doc_fd;
int	g_signal;

/*
 * Function: handle_signal
 * ------------------------
 * Signal handler function to handle SIGINT (Ctrl+C) signal. This function is
 * typically invoked when the user interrupts the program by pressing Ctrl+C.
 *
 * sig: The signal number received by the handler.
 */
void	handle_signal_rl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_signal = 1;
	}
}

void	handle_signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_signal = 1;
	}
}

void	handle_signal_hd(int sig)
{
	if (sig == SIGINT)
	{
		close(g_here_doc_fd);
		g_here_doc_fd = -1;
		write(1, "\n", 1);
		g_signal = 1;
	}
}

/*
 * Function: main
 * ---------------
 * Entry point of the program. This function initializes the minishell,
 * sets up signal handling for SIGINT and SIGQUIT, and then enters
 * the main loop to fetch and process user input.
 *
 * argc: Number of command-line argv passed to the program.
 * argv: Array of strings containing the command-line argv.
 * envp: Array of strings containing the environment variables.
 *
 * returns: The exit status of the program.
 */
int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Minishell cannot take arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	return (fetch_line(envp));
}
