/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:37 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/14 18:05:22 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (false);
	return (true);
}

bool	ft_islong(char *s)
{
	unsigned long	nb;
	int				sign;
	size_t			i;

	i = 0;
	sign = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isstr(s + i))
		return (false);
	nb = 0;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		nb = 10 * nb + (s[i++] - '0');
		if (nb + sign > LONG_MAX)
			return (false);
	}
	return (true);
}

bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
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
