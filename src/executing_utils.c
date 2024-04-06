/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:05:57 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/06 15:45:29 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*cmd_path;
	size_t	i;

	cmd_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2 * sizeof(char));
	i = 0;
	while (*path)
		cmd_path[i++] = *path++;
	cmd_path[i++] = '/';
	while (*cmd)
		cmd_path[i++] = *cmd++;
	cmd_path[i] = '\0';
	return (cmd_path);
}

char	*ft_which(char **paths, char *cmd)
{
	char	*cmd_path;
	size_t	i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin_path(paths[i++], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

int	nb_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
