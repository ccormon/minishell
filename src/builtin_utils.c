/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:04:59 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/08 11:03:52 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: create_new_var
 * -------------------------
 * Creates a new environment variable with the given name and content and adds 
 * it to the environment.
 *
 * arg:     Pointer to a structure containing command arguments and settings.
 * name:    Name of the environment variable.
 * content: Content of the environment variable.
 */
static void	create_new_var(t_arg *arg, char *name, char *content)
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

/*
 * Function: fill_old_var
 * -----------------------
 * Updates the content of an existing environment variable.
 *
 * var:     Pointer to the environment variable.
 * name:    Name of the environment variable.
 * content: Content of the environment variable.
 */
static void	fill_old_var(char **var, char *name, char *content)
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

/*
 * Function: rewrite_evar
 * -----------------------
 * Rewrites an environment variable with the given name and content.
 * If the variable does not exist, it creates a new one.
 *
 * arg:     Pointer to a structure containing command arguments and settings.
 * name:    Name of the environment variable.
 * content: Content of the environment variable.
 */
void	rewrite_evar(t_arg *arg, char *name, char *content)
{
	char	**var;

	var = find_var(arg->envp, name);
	if (!var)
		create_new_var(arg, name, content);
	else
		fill_old_var(var, name, content);
}
