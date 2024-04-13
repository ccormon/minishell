/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:52:15 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/13 12:06:52 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
