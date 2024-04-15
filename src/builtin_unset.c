/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:20 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/15 12:09:23 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: shift_tab
 * --------------------
 * Shifts all elements in a string array by one position to the left.
 *
 * tab: Pointer to the string array to be shifted.
 */
static void	shift_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	free(tab[i]);
	while (tab[i + 1])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	tab[i] = NULL;
}

/*
 * Function: exec_unset
 * ---------------------
 * Executes the 'unset' built-in command to remove an environment variable.
 *
 * arg: Pointer to a structure containing command arguments and settings.
 * str: Name of the environment variable to unset.
 */
static void	exec_unset(t_arg *arg, char *str)
{
	int		i;
	char	**name;

	i = 0;
	name = NULL;
	name = find_var(arg->envp, str);
	if (!name)
		return ;
	if (*(*name + ft_strlen(str)) != '=')
		return ;
	shift_tab(name);
}

/*
 * Function: builtin_unset
 * ------------------------
 * Executes the 'unset' built-in command to remove environment variables.
 *
 * arg:  Pointer to a structure containing command arguments and settings.
 * argv: Array of command arguments.
 */
void	builtin_unset(t_arg *arg, char **argv)
{
	int	i;
	int	j;

	i = 0;
	arg->exit_code = EXIT_SUCCESS;
	if (argv[1])
	{
		while (argv[++i])
		{
			j = 0;
			while (ft_isalnum(argv[i][j]) || argv[i][j] == '_')
				j++;
			if (argv[i][j] != '\0'
				|| (!ft_isalpha(argv[i][0]) && argv[i][0] != '_'))
			{
				ft_putstr_fd("unset : not a valid identifier\n", STDERR_FILENO);
				arg->exit_code = GENERAL_ERR;
			}
			else
				exec_unset(arg, argv[i]);
		}
	}
}
