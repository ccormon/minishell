/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:26:54 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/03 14:24:27 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: free_tab
 * -------------------
 * Frees the memory allocated for a dynamically allocated array of strings.
 *
 * tab: Pointer to the array of strings to be freed.
 */
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_lst(t_tmp_list *lst)
{
	t_tmp_list	*new;

	while (lst != NULL)
	{
		new = lst->next;
		free(lst->content);
		free(lst);
		lst = new;
	}
}

void	free_cmd_lst(t_cmd *lst)
{
	t_cmd	*new;

	while (lst != NULL)
	{
		new = lst->next;
		free_tab(lst->arguments);
		free(lst->input_redir);
		free(lst->output_redir);
		free_tab(lst->input_file);
		free_tab(lst->output_file);
		free(lst);
		lst = new;
	}
}

void	ft_exit(t_arg *arg) // si arg exit code = arg
{
	rl_clear_history();
	free(arg->prompt);
	free(arg->whole_line);
	free_tab(arg->paths);
	free_tab(arg->envp);
	//free_lst(arg->lexing);
	//free_cmd_lst(arg->cmd_list);
	//exit(arg->exit_code);
}
