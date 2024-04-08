/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:51:28 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:05:48 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**find_var(char **envp, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (*envp)
	{
		j = 0;
		while ((*envp)[j] == to_find[j])
		{
			j++;
			if (!to_find[j])
				return (envp);
		}
		envp++;
	}
	return (NULL);
}

static void	exec_export(t_arg *arg, char *str)
{
	int		i;
	int		j;
	char	*name;
	char	*content;

	i = 0;
	j = 0;
	name = malloc(ft_strlen(str) + 1);
	content = malloc(ft_strlen(str) + 1);
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = str[i];
	name[++i] = '\0';
	while (str[i + j])
	{
		content[j] = str[i + j];
		j++;
	}
	content[j] = '\0';
	rewrite_evar(arg, name, content);
	free(content);
	free(name);
}

void	builtin_export(t_arg *arg, char **argv, int fd)
{
	int	i;
	int	j;

	i = 0;
	arg->exit_code = 0;
	if (!argv[1])
		builtin_env(arg, NULL, fd);
	while (argv[++i])
	{
		j = 0;
		while (ft_isalnum(argv[i][j]) || argv[i][j] == '_')
			j++;
		if (argv[i][j] != '=' || (!ft_isalpha(argv[i][0]) && argv[i][0] != '_'))
		{
			ft_putstr_fd("export : not a valid identifier\n", 2);
			arg->exit_code = 1;
		}
		else
			exec_export(arg, argv[i]);
	}
}
