/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:30 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/14 11:46:30 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: builtin_echo
 * -----------------------
 * Executes the 'echo' built-in command.
 *
 * arg:   Pointer to a structure containing command arguments and settings.
 * argv:  Array of command arguments.
 * fd:    File descriptor for output.
 */
void	builtin_echo(t_arg *arg, char **argv, int fd)
{
	int		i;
	int		j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
	arg->exit_code = EXIT_SUCCESS;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
	{
		while (argv[1][j] == 'n')
			j++;
		if (!argv[1][j] && i++)
			new_line = false;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], fd);
		if (argv[i])
			ft_putstr_fd(" ", fd);
	}
	if (!new_line)
		return ;
	ft_putstr_fd("\n", fd);
}
