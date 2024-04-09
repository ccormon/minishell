/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:52:15 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/09 11:09:58 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

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
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (fetch_line(envp));
}
