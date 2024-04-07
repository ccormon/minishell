/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:17:50 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/06 19:56:14 by sdemaude         ###   ########.fr       */
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
		handle_multiple_cmd(arg, arg->cmd_list);
}
