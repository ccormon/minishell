/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:39:25 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/13 13:51:06 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Function: find_str
 * -------------------
 * Searches for a specific string in the array of environment variables (envp).
 * It returns a pointer to the beginning of the value associated with the given
 * string.
 *
 * envp:   Array of strings containing the environment variables.
 * to_find: The string to search for.
 * skip:    Number of characters to skip before returning the found string.
 *
 * returns: A pointer to the beginning of the value associated with the
 *			given string if found, or NULL if the string is not found in
 *			the environment variables.
 */
char	*find_str(char **envp, char *to_find, int skip)
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
				return (*envp + skip);
		}
		envp++;
	}
	return (NULL);
}

/*
 * Function: get_prompt
 * ---------------------
 * Generates the prompt string for the minishell based on environment variables.
 * The prompt typically includes the username and session information.
 *
 * envp: Array of strings containing the environment variables.
 *
 * returns: A dynamically allocated string representing the prompt.
 *          It is the responsibility of the caller to free the memory allocated
 *          for the prompt.
 */
char	*get_prompt(char **envp)
{
	char	*prompt;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	tmp1 = find_str(envp, "LOGNAME=", 8);
	if (!tmp1)
		return (ft_strdup("minishell>$ "));
	tmp2 = modft_strjoin(tmp1, "@");
	tmp1 = find_str(envp, "SESSION_MANAGER=local/", 22);
	while (tmp1[i] != '.')
		i++;
	tmp1[i] = '\0';
	prompt = modft_strjoin(tmp2, tmp1);
	tmp1 = modft_strjoin(prompt, ">$ ");
	free(prompt);
	prompt = tmp1;
	free(tmp2);
	return (prompt);
}

/*
 * Function: count_token
 * ----------------------
 * Counts the number of occurrences of a specific token in the linked list.
 *
 * lexing: Pointer to the head of the linked list.
 * token:  Token to be counted.
 *
 * returns: Number of occurrences of the token.
 */
int	count_token(t_tmp_list *lexing, t_token token)
{
	int	count;

	count = 0;
	while (lexing)
	{
		if (lexing->token == token)
			count++;
		lexing = lexing->next;
	}
	return (count);
}
