/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:37 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/01 11:26:26 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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
