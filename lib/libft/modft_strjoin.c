/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modft_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:21:45 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/04 11:00:56 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*modft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	char	*dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s1)
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
