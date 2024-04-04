/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:37 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/03 13:09:59 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (true);
	return (false);
}

bool	ft_isseparator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	ft_ismetachar(char c)
{
	if (c == '\\' || c == '`' || c == ';' || c == '*'
		|| c == '(' || c == ')' || c == '#' || c == '&' || c == '~'
		|| c == '{' || c == '}')
		return (true);
	return (false);
}
