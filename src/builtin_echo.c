/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:30 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/07 20:40:15 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// problem when redirecting in another file maybe the fd ?
void	builtin_echo(t_arg *arg, char **argv, int fd)
{
	int		i;
	int		j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
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
	arg->exit_code = 0;
	if (!new_line)
		return ;
	ft_putstr_fd("\n", fd);
}
