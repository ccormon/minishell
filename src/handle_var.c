/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:49:13 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/07 13:47:25 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: get_var_content
 * --------------------------
 * Retrieves the content of an environment variable.
 *
 * arg: Pointer to a structure containing command argv and settings.
 * str: Pointer to the environment variable name string.
 *
 * returns: Pointer to the content of the environment variable,
 * or NULL if not found.
 */
static char	*get_var_content(t_arg *arg, char *str)
{
	int		i;
	char	*tmp;
	char	*content;

	i = 0;
	str++;
	if (*str == '?')
		return (ft_itoa(arg->exit_code));
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (*str && (ft_isalnum(*str) || *str == '_'))
	{
		tmp[i] = *str;
		i++;
		str++;
	}
	tmp[i] = '=';
	tmp[i + 1] = '\0';
	content = find_str(arg->envp, tmp, ft_strlen(tmp));
	free(tmp);
	return (content);
}

/*
 * Function: rewrite_str
 * ----------------------
 * Rewrites a string by inserting another string at a specified index.
 *
 * str: Pointer to the original string.
 * new: Pointer to the string to be inserted.
 * i:   Index at which the insertion should occur.
 *
 * returns: Pointer to the rewritten string.
 */
static char	*rewrite_str(char *str, char *new, int i)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(new) + 1));
	i++;
	ft_strlcpy(new_line, str, i);
	mod_strcat(new_line, new);
	if (str[i] == '?')
		i++;
	else
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	mod_strcat(new_line, str + i);
	free(str);
	return (new_line);
}

/*
 * Function: create_new_node
 * --------------------------
 * Creates a new node in the linked list by splitting the content of
 * the current node.
 *
 * list: Pointer to a pointer to the current node in the linked list.
 *
 * returns: 0 if the new node is created successfully.
 */
static int	create_new_node(t_tmp_list **list)
{
	int		i;
	int		tab_size;
	char	**tab;

	i = -1;
	while ((*list)->content[++i])
		if ((*list)->content[i] == '\t')
			(*list)->content[i] = ' ';
	tab = ft_split((*list)->content, ' ');
	tab_size = 0;
	while (tab[tab_size])
		tab_size++;
	i = 0;
	free((*list)->content);
	(*list)->content = ft_strdup(tab[i]);
	while (++i < tab_size)
	{
		(*list)->token = TOKEN_WORD;
		mod_lstadd_back(list, mod_lstnew(mod_strdup(tab[i],
					ft_strlen(tab[i]))));
		*list = (*list)->next;
	}
	return (0);
}

/*
 * Function: replace_env_var
 * --------------------------
 * Replaces environment variables in the content of the current node with
 * their values.
 * If the value contains spaces or tabs and the node is not in quotes, it
 * creates new nodes for each part of the value.
 *
 * arg:   Pointer to a structure containing command argv and settings.
 * list:  Pointer to a pointer to the current node in the linked list.
 * state: Current parsing state indicating if the node is in quotes.
 * i:     Index indicating the start position of the environment variable.
 *
 * returns: Updated index after replacing the environment variable.
 */
int	replace_env_var(t_arg *arg, t_tmp_list **list, int state, int i)
{
	int		len;
	char	*replace;

	replace = get_var_content(arg, (*list)->content + i);
	if (!replace)
	{
		len = 1;
		while ((*list)->content[len + i]
			&& (ft_isalnum((*list)->content[len + i])
				|| (*list)->content[len + i] == '_'))
			len++;
		shift_str((*list)->content + i, len);
		return (i);
	}
	else
		(*list)->content = rewrite_str((*list)->content, replace, i);
	if (state == 0 && (ft_strrchr(replace, ' ') || ft_strrchr(replace, '\t')))
		return (create_new_node(list));
	return (i + ft_strlen(replace));
}
