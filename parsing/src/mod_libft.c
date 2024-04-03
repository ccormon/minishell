/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:33:37 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/02 18:16:25 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*
 * Function: mod_strcat
 * ---------------------
 * Concatenates the content of the source string to the end of
 * the destination string.
 *
 * dest: Pointer to the destination string.
 * src:  Pointer to the source string.
 */
void	mod_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(dest);
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

/*
 * Function: mod_strdup
 * ---------------------
 * Copies a specified length of characters from a string and returns
 * the resulting substring.
 *
 * str: Pointer to the source string.
 * len: Length of the substring to be copied.
 *
 * returns: Pointer to the dynamically allocated substring.
 */
char	*mod_strdup(char *str, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == 0)
		return (0);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
 * Function: mod_lstnew
 * ---------------------
 * Creates a new node for a linked list with the specified content
 * and token type.
 *
 * content: Pointer to the content string for the new node.
 *
 * returns: Pointer to the newly created node.
 */
t_tmp_list	*mod_lstnew(char *content)
{
	t_tmp_list	*new;

	new = malloc(sizeof(t_tmp_list));
	if (!new)
		return (0);
	new->content = content;
	new->token = TOKEN_WORD;
	if (content[0] == '|')
		new->token = TOKEN_PIPE;
	else if (content[0] == '>' && content[1] == '>')
		new->token = TOKEN_APPEND;
	else if (content[0] == '>')
		new->token = TOKEN_OUTFILE;
	else if (content[0] == '<' && content[1] == '<')
		new->token = TOKEN_HEREDOC;
	else if (content[0] == '<')
		new->token = TOKEN_INFILE;
	new->next = NULL;
	return (new);
}

/*
 * Function: mod_lstadd_back
 * --------------------------
 * Adds a new node to the end of a linked list.
 *
 * lst: Pointer to a pointer to the head of the linked list.
 * new: Pointer to the new node to be added.
 */
void	mod_lstadd_back(t_tmp_list **lst, t_tmp_list *new)
{
	while (*lst != NULL)
		lst = &(*lst)->next;
	*lst = new;
}
