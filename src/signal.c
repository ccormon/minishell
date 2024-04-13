/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:00:08 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/13 14:56:33 by sdemaude         ###   ########.fr       */
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

/*
 * Function: handle_signal_cmd
 * ---------------------------
 * Handles signals for command mode.
 *
 * sig: The signal number.
 */
void	handle_signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_signal = 1;
	}
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

/*
 * Function: handle_signal_hd
 * --------------------------
 * Handles signals for here-document mode.
 *
 * sig: The signal number.
 */
void	handle_signal_hd(int sig)
{
	if (sig == SIGINT)
	{
		close(g_here_doc_fd);
		g_here_doc_fd = -1;
		write(1, "\n", 1);
		g_signal = 1;
	}
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}

/*
 * Function: sig_exit_code
 * ------------------------
 * Sets the exit code based on the received signal.
 *
 * arg: Pointer to the argument structure.
 */
void	sig_exit_code(t_arg *arg)
{
	if (g_signal == 1)
	{
		arg->exit_code = CTRL_C;
		g_signal = 0;
	}
}

/*
 * Function: change_signal
 * ------------------------
 * Changes the signal handling based on the parameter value.
 *
 * param: The parameter value.
 */
void	change_signal(int param)
{
	if (param == 0)
	{
		signal(SIGINT, &handle_signal_rl);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (param == 1)
	{
		signal(SIGINT, &handle_signal_cmd);
		signal(SIGQUIT, &handle_signal_cmd);
	}
	else
	{
		signal(SIGINT, &handle_signal_hd);
		signal(SIGQUIT, &handle_signal_hd);
	}
}
