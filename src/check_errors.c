/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:43 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/09 11:08:02 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

/*
 * Function: print_error
 * ----------------------
 * Prints an error message to the standard error stream and sets the exit code.
 *
 * arg: Pointer to a structure containing command argv and settings.
 * str: Pointer to the error message string to be printed.
 *
 * returns: false
 */
static bool	print_error(t_arg *arg, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	arg->exit_code = GENERAL_ERR;
	return (false);
}

/*
 * Function: check_pipe_errors
 * ----------------------------
 * Checks for syntax errors related to pipe in the provided command string.
 *
 * str: Pointer to the command string to be checked for pipe errors.
 *
 * returns: true if no pipe errors are found, false otherwise.
 */
bool	check_pipe_errors(char *str)
{
	if (*str == '|')
	{
		str++;
		while (ft_isspace(*str))
			str++;
		if (*str == '|' || !*str)
			return (false);
	}
	return (true);
}

/*
 * Function: check_redir_errors
 * -----------------------------
 * Checks for syntax errors related to redirection in the provided command
 * string.
 *
 * str: Pointer to the command string to be checked for redirection errors.
 *
 * returns: true if no redirection errors are found, false otherwise.
 */
bool	check_redir_errors(char *str)
{
	if (*str == '>' || *str == '<')
	{
		if (*(str + 1) == *str)
			str++;
		str++;
		while (ft_isspace(*str))
			str++;
		if (ft_isseparator(*str) || !*str)
			return (false);
	}
	return (true);
}

/*
 * Function: in_quotes
 * --------------------
 * Updates the parsing state based on the occurrence of quotes in the command
 * string.
 *
 * c:      The character being processed in the command string.
 * state:  Pointer to the parsing state variable.
 */
void	in_quotes(char c, int *state)
{
	if (c == '\'')
	{
		if ((*state) == 0)
			*state = 1;
		else if ((*state) == 1)
			*state = 0;
	}
	if (c == '\"')
	{
		if ((*state) == 0)
			*state = 2;
		else if ((*state) == 2)
			*state = 0;
	}
}

/*
 * Function: check_errors
 * -----------------------
 * Checks for syntax errors in the provided command string.
 *
 * arg: Pointer to a structure containing command argv and settings.
 * str: Pointer to the command string to be checked for errors.
 *
 * returns: true if no syntax errors are found, false otherwise.
 */
bool	check_errors(t_arg *arg, char *str)
{
	int	state;

	state = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '|')
		return (print_error(arg, "Pipe error\n"));
	while (*str)
	{
		if (state == 0 && !check_pipe_errors(str))
			return (print_error(arg, "Pipe error\n"));
		else if (state == 0 && !check_redir_errors(str))
			return (print_error(arg, "Redirection error\n"));
		else if (state == 0 && ft_ismetachar(*str))
			return (print_error(arg, "Metacharacter not handled\n"));
		in_quotes(*str, &state);
		str++;
	}
	if (state != 0)
		return (print_error(arg, "Quotes must be closed\n"));
	return (true);
}
