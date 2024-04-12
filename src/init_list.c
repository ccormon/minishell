/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:59:30 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/12 14:27:07 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: cmd_lstnew
 * ---------------------
 * Creates a new command node in the command list.
 *
 * arg: Pointer to a structure containing command argv and settings.
 *
 * returns: Pointer to the newly created command node.
 */
static t_cmd	*cmd_lstnew(t_arg *arg)
{
	int		count;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->cmd_path = NULL;
	count = count_token(arg->lexing, TOKEN_WORD) + 1;
	new->argv = ft_calloc(count, sizeof(char *));
	count = count_token(arg->lexing, TOKEN_INFILE)
		+ count_token(arg->lexing, TOKEN_HEREDOC) + 1;
	new->input_redir = ft_calloc(count, sizeof(int));
	new->input_file = ft_calloc(count, sizeof(char *));
	count = count_token(arg->lexing, TOKEN_OUTFILE)
		+ count_token(arg->lexing, TOKEN_APPEND) + 1;
	new->output_redir = ft_calloc(count, sizeof(int));
	new->output_file = ft_calloc(count, sizeof(char *));
	new->next = NULL;
	return (new);
}

/*
 * Function: cmd_lstadd_back
 * --------------------------
 * Adds a new command node to the end of the command list.
 *
 * lst: Pointer to a pointer to the head of the command list.
 * new: Pointer to the new command node to be added.
 */
static void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = new;
}

/*
 * Function: fill_tab
 * -------------------
 * Fills the input_file or output_file array in the command node with
 * the specified token.
 *
 * lexing: Pointer to the current node in the lexing list.
 * cmd:    Pointer to the command node in the command list.
 * token:  Token indicating the type of redirection (TOKEN_INFILE,
 * TOKEN_HEREDOC, TOKEN_OUTFILE, or TOKEN_APPEND).
 */
static void	fill_tab(t_tmp_list *lexing, t_cmd *cmd, t_token token)
{
	int	i;

	i = 0;
	if (token == TOKEN_INFILE || token == TOKEN_HEREDOC)
	{
		while (cmd->input_file[i])
			i++;
		cmd->input_file[i] = mod_strdup(lexing->next->content,
				ft_strlen(lexing->next->content));
		cmd->input_redir[i] = token;
	}
	if (token == TOKEN_OUTFILE || token == TOKEN_APPEND)
	{
		while (cmd->output_file[i])
			i++;
		cmd->output_file[i] = mod_strdup(lexing->next->content,
				ft_strlen(lexing->next->content));
		cmd->output_redir[i] = token - 2;
	}
}

/*
 * Function: fill_word
 * --------------------
 * Fills the argument array in the command node with the content of a WORD token.
 *
 * cmd: Pointer to a pointer to the current command node in the command list.
 * tmp: Pointer to the current node in the lexing list.
 * i:   Index to insert the content in the argument array.
 *
 * returns: Updated index after filling the argument array.
 */
static int	fill_word(t_cmd **cmd, t_tmp_list *tmp, int i)
{
	while ((*cmd)->argv[i])
		i++;
	(*cmd)->argv[i] = mod_strdup(tmp->content,
			ft_strlen(tmp->content));
	return (i);
}

/*
 * Function: init_cmd_list
 * ------------------------
 * Initializes the command list based on the lexing list.
 *
 * arg: Pointer to a structure containing command argv and settings.
 * cmd: Pointer to a pointer to the head of the command list.
 * tmp: Pointer to the head of the lexing list.
 */
void	init_cmd_list(t_arg *arg, t_cmd **cmd, t_tmp_list *tmp)
{
	int	i;

	i = 0;
	arg->cmd_list = NULL;
	cmd_lstadd_back(cmd, cmd_lstnew(arg));
	while (tmp)
	{
		if (!*tmp->content)
			tmp = tmp->next;
		if (!tmp)
			break ;
		if (tmp->token != TOKEN_WORD && tmp->token != TOKEN_PIPE)
		{
			fill_tab(tmp, *cmd, tmp->token);
			tmp = tmp->next;
		}
		else if (tmp->token == TOKEN_WORD)
			i = fill_word(cmd, tmp, i);
		else if (tmp->token == TOKEN_PIPE)
		{
			i = 0;
			if (!(*cmd)->argv[0])
				(*cmd)->argv[0] = mod_strdup("cat", 3);
			cmd_lstadd_back(cmd, cmd_lstnew(arg));
			cmd = &(*cmd)->next;
		}
		tmp = tmp->next;
	}
}
