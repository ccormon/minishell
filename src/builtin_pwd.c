/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:55:57 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:12:59 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: builtin_pwd
 * ----------------------
 * Executes the 'pwd' built-in command to print the current working directory.
 *
 * arg: Pointer to a structure containing command arguments and settings.
 * fd:  File descriptor for output.
 */
void	builtin_pwd(t_arg *arg, int fd)
{
	ft_putstr_fd(arg->pwd, fd);
	ft_putstr_fd("\n", fd);
	arg->exit_code = 0;
}
