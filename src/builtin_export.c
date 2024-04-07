/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 10:51:28 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/07 20:40:30 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

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

void	create_new_var(t_arg *arg, char *name, char *content)
{
	int		i;
	int		len_tab;
	char	**tmp_tab;

	i = -1;
	len_tab = 0;
	while (arg->envp[len_tab])
		len_tab++;
	tmp_tab = malloc(sizeof(char *) * (len_tab + 2));
	while (arg->envp[++i])
		tmp_tab[i] = arg->envp[i];
	tmp_tab[i] = ft_strjoin(name, content);
	tmp_tab[i + 1] = NULL;
	free(arg->envp);
	arg->envp = tmp_tab;
}

void	fill_old_var(char **var, char *name, char *content)
{
	int		i;
	int		j;
	int		len_str;
	char	*tmp_str;

	i = -1;
	j = -1;
	len_str = 0;
	tmp_str = malloc(ft_strlen(name) + ft_strlen(content) + 1);
	while ((*var)[++i] != '=')
		tmp_str[i] = (*var)[i];
	tmp_str[i++] = '=';
	while (content[++j])
		tmp_str[i + j] = content[j];
	tmp_str[i + j] = '\0';
	free(*var);
	*var = tmp_str;
}

void	rewrite_evar(t_arg *arg, char *name, char *content)
{
	char	**var;

	var = find_var(arg->envp, name);
	if (!var)
		create_new_var(arg, name, content);
	else
		fill_old_var(var, name, content);
	free(content);
}

void	exec_export(t_arg *arg, char *str)
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
	i++;
	name[i] = '\0';
	while (str[i + j])
	{
		content[j] = str[i + j];
		j++;
	}
	content[j] = '\0';
	rewrite_evar(arg, name, content);
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
