/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:30:30 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/04 18:00:44 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_echo(t_arg *arg, int fd)
{
	int		i;
	int		j;
	bool	new_line;

	i = 1;
	j = 1;
	new_line = true;
	if (arg->cmd_list->argv[1] && ft_strncmp(arg->cmd_list->argv[1], "-n", 2))
	{
		while (arg->cmd_list->argv[1][i] == 'n')
			j++;
		if (!arg->cmd_list->argv[1][j])
		{
			new_line = false;
			i++;
		}
	}
	while (arg->cmd_list->argv[i])
	{
		ft_putstr_fd(arg->cmd_list->argv[i++], fd);
		if (arg->cmd_list->argv[i])
			ft_putstr_fd(" ", fd);
	}
	if (new_line)
		ft_putstr_fd("\n", fd);
}
