/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:21:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/28 17:33:53 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBFT */

# include "libft/libft.h"

/* INCLUDES */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>

/* DEFINES */

# define GENERAL_ERR 1
# define EXEC_CMD_KO 126
# define INVALID_CMD 127
# define TMP_FILE "/tmp/tmp"

/* STRUCTURES */

typedef struct s_cmd
{
	char	*whole_cmd; // echo -n hi there
	char	*cmd_name; // echo
	char	*cmd_path; // init to NULL
	char	**arguments; // split de whole_cmd
	int		status;
	int		pid_child;
	int		*input_redir; // init to NULL; > = 1; << = 2;
	char	**input_file; // init to NULL
	int		input_fd;
	int		*output_redir; // init to NULL; > = 1; >> = 2;
	char	**output_file; // init to NULL
	int		output_fd;
	bool	builtin;
	t_cmd	*next;
}	t_cmd;

typedef struct s_arg
{
	int		exit_code;
	char	*prompt;
	char	*whole_line;
	char	**arg_tab;
	char	**paths;
	t_cmd	*cmd_list;
	int		pipe_fd[2][2];
}	t_arg;

/* FONCTIONS */

// Executing
void	executing(t_arg *param, char **envp);
//  handle_redirections
int		nb_redir(t_cmd *cmd);
void	read_input(int tmp_fd, char *lim_lr);
int		open_hd(t_cmd *cmd, int i);
int		handle_redir_input(t_cmd *cmd);
int		handle_redir_output(t_cmd *cmd);
//  one_command
int		exec_one_cmd(t_arg *arg, char **envp);
int		handle_one_cmd(t_arg *arg, char **envp);
//  utils
char	*ft_strjoin_path(char *path, char *cmd);
char	*ft_which(char **paths, char *cmd);

#endif
