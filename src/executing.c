/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/12 18:42:48 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executing(t_arg *arg)
{
	arg->nb_cmd = nb_cmd(arg->cmd_list);
	if (arg->nb_cmd == 0)
		return ;
	else if (arg->nb_cmd == 1)
		handle_one_cmd(arg);
	else if (arg->nb_cmd > 1)
		handle_multi_cmd(arg, arg->cmd_list);
	if (g_signal == 1)
		arg->exit_code = CTRL_C;
}
