/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:37 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/04 14:27:23 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_islong(char *s)
{
	long long	nb;
	int			sign;
	size_t		i;

	i = 0;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (false);
	i = 0;
	sign = 1;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		nb = 10 * nb + s[i++] - '0';
		if (nb * sign < LONG_MIN || nb > LONG_MAX)
			return (false);
	}
	return (true);
}

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
