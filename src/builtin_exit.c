/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:58:21 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/13 20:24:48 by sdemaude         ###   ########.fr       */
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

/*
 * Function: free_lst
 * -------------------
 * Frees the memory allocated for the lexing list.
 *
 * lst: Pointer to the head of the lexing list.
 */
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

/*
 * Function: free_cmd_lst
 * -----------------------
 * Frees the memory allocated for the command list.
 *
 * lst: Pointer to the head of the command list.
 */
void	free_cmd_lst(t_cmd *lst)
{
	t_cmd	*new;

	while (lst != NULL)
	{
		new = lst->next;
		free(lst->cmd_path);
		free_tab(lst->argv);
		free(lst->input_redir);
		free(lst->output_redir);
		free_tab(lst->input_file);
		free_tab(lst->output_file);
		free(lst);
		lst = new;
	}
}

/*
 * Function: get_exit_code
 * ------------------------
 * Retrieves the exit code from the arguments provided to the 'exit' built-in.
 *
 * arg:   Pointer to a structure containing command arguments and settings.
 * argv:  Array of command arguments.
 *
 * returns: True if the exit code is successfully retrieved; otherwise, false.
 */
bool	get_exit_code(t_arg *arg, char **argv)
{
	if (argv[1])
	{
		if (!ft_islong(argv[1]))
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			arg->exit_code = BUILTIN_KO;
		}
		else if (argv[2])
		{
			ft_putstr_fd("exit : too many arguments\n", 2);
			arg->exit_code = GENERAL_ERR;
			return (false);
		}
		else
			arg->exit_code = ft_atoi(argv[1]);
	}
	return (true);
}

/*
 * Function: builtin_exit
 * -----------------------
 * Executes the 'exit' built-in command.
 *
 * arg:      Pointer to a structure containing command arguments and settings.
 * argv:     Array of command arguments.
 * builtin:  Indicates whether the 'exit' command is invoked as a built-in.
 */
void	builtin_exit(t_arg *arg, char **argv, bool builtin)
{
	if (arg->nb_cmd <= 1)
	{
		write(1, "exit\n", 5);
		if (builtin)
		{
			if (!get_exit_code(arg, argv))
				return ;
			free_lst(arg->lexing);
			free_cmd_lst(arg->cmd_list);
		}
		rl_clear_history();
		free(arg->prompt);
		free(arg->whole_line);
		free(arg->pwd);
		free_tab(arg->paths);
		free_tab(arg->envp);
		exit(arg->exit_code);
	}
}
