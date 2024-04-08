/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:04:59 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 10:05:59 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}
