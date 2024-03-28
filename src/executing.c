/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/28 17:37:31 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_multiple_cmd(t_arg *arg, char **envp)
{

}

void	executing(t_arg *arg, char **envp)
{
	if (!arg->cmd_list->next)
	{
		// execute one command
		arg->exit_code = handle_one_cmd(arg, envp);
	}
	else
	{
		// execute multiple command
		arg->exit_code = handle_multiple_cmd(arg, envp);
	}
}
