/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:01:38 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/07 19:20:17 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_env(t_arg *arg, char **argv, int fd)
{
	int	i;

	i = 0;
	if (argv && argv[1])
	{
		ft_putstr_fd("env : No such file or directory\n", 2);
		arg->exit_code = 127;
		return ;
	}
	while (arg->envp[i])
	{
		ft_putstr_fd(arg->envp[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	arg->exit_code = 0;
}
