/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:55:57 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/07 20:40:19 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_pwd(t_arg *arg, int fd)
{
	ft_putstr_fd(arg->pwd, fd);
	ft_putstr_fd("\n", fd);
	arg->exit_code = 0;
}
