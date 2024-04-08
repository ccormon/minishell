/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:50:20 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:05:52 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shift_tab(char **tab)
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

void	exec_unset(t_arg *arg, char *str)
{
	int		i;
	char	*name;

	i = 0;
	name = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	shift_tab(find_var(arg->envp, name));
	free(name);
}

void	builtin_unset(t_arg *arg, char **argv)
{
	int	i;
	int	j;

	i = 0;
	arg->exit_code = 0;
	if (argv[1])
	{
		while (argv[++i])
		{
			j = 0;
			while (ft_isalnum(argv[i][j]) || argv[i][j] == '_')
				j++;
			if (argv[i][j] != '\0' || (!ft_isalpha(argv[i][0])
				&& argv[i][0] != '_'))
			{
				ft_putstr_fd("unset : not a valid identifier\n", 2);
				arg->exit_code = 1;
			}
			else
				exec_unset(arg, argv[i]);
		}
	}
}
