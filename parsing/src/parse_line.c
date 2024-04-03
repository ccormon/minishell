/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:26 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/02 17:59:31 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*
 * Function: shift_str
 * --------------------
 * Shifts characters in a string to the left by a specified length.
 *
 * str: Pointer to the string to be shifted.
 * len: Length by which characters are to be shifted.
 */
void	shift_str(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i + len])
	{
		str[i] = str[i + len];
		i++;
	}
	str[i] = '\0';
}

/*
 * Function: next_element
 * -----------------------
 * Determines the length of the next element in the command string.
 *
 * str: Pointer to the command string.
 *
 * returns: The length of the next element.
 */
static int	next_element(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	while (str[i])
	{
		if (ft_isseparator(str[i]) && ft_isseparator(str[i + 1]))
			return (2);
		else if (ft_isseparator(str[i]))
			return (1);
		else
		{
			while (str[i] && ((!ft_isspace(str[i]) && !ft_isseparator(str[i]))
					|| state != 0))
			{
				in_quotes(str[i], &state);
				i++;
			}
			return (i);
		}
	}
	return (i);
}

/*
 * Function: remove_quotes
 * ------------------------
 * Removes quotes from the content of each node in the linked list.
 *
 * arg:  Pointer to a structure containing command arguments and settings.
 * list: Pointer to the head of the linked list.
 */
static void	remove_quotes(t_arg *arg, t_tmp_list *list)
{
	int	i;
	int	state;

	state = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->content[i])
		{
			in_quotes(list->content[i], &state);
			if ((list->content[i] == '\"' && state != 1)
				|| (list->content[i] == '\'' && state != 2))
				shift_str(list->content + i, 1);
			else if (list->content[i] == '$' && state != 1)
				i = replace_env_var(arg, &list, state, i);
			else
				i++;
		}
		list = list->next;
	}
}

/*
 * Function: lexing
 * ----------------
 * Tokenizes the command string into lexical units (tokens) and creates a linked
 * list of tokens.
 *
 * arg: Pointer to a structure containing command arguments and settings.
 * str: Pointer to the command string to be tokenized.
 */
static void	lexing(t_arg *arg, char *str)
{
	int	size;

	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		size = next_element(str);
		if (size != 0)
			mod_lstadd_back(&arg->lexing, mod_lstnew(mod_strdup(str, size)));
		str += size;
	}
	remove_quotes(arg, arg->lexing);
}

/*
 * Function: parse_line
 * ---------------------
 * Parses the whole command line by performing error checking, lexical analysis,
 * and initialization of the command list.
 *
 * arg: Pointer to a structure containing command arguments and settings.
 *
 * returns: true if the line is parsed successfully, false otherwise.
 */
bool	parse_line(t_arg *arg)
{
	if (!check_errors(arg, arg->whole_line))
		return (false);
	lexing(arg, arg->whole_line);
	init_cmd_list(arg, &arg->cmd_list, arg->lexing);
	return (true);
}
