/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:58:21 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/04 18:02:15 by sdemaude         ###   ########.fr       */
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
		free_tab(lst->argv);
		free(lst->input_redir);
		free(lst->output_redir);
		free_tab(lst->input_file);
		free_tab(lst->output_file);
		free(lst);
		lst = new;
	}
}

bool	get_exit_code(t_arg *arg)
{
	if (arg->cmd_list->argv[1])
	{
		if (!ft_islong(arg->cmd_list->argv[1]))
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			arg->exit_code = 2;
		}
		else if (arg->cmd_list->argv[2])
		{
			ft_putstr_fd("exit : too many arguments\n", 2);
			arg->exit_code = 1;
			return (false);
		}
		else
			arg->exit_code = ft_atoi(arg->cmd_list->argv[1]);
	}
	return (true);
}

void	builtin_exit(t_arg *arg, bool builtin)
{
	if (arg->nb_cmd <= 1)
	{
		write(1, "exit\n", 5);
		if (builtin)
		{
			if (!get_exit_code(arg))
				return ;
			free_lst(arg->lexing);
			free_cmd_lst(arg->cmd_list);
		}
		rl_clear_history();
		free(arg->prompt);
		free(arg->whole_line);
		free_tab(arg->paths);
		free_tab(arg->envp);
		exit(arg->exit_code);
	}
}
