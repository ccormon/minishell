/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:21:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/22 18:38:31 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define INVALID_CMD 127
# define TMP_FILE "/tmp/tmp"

/* STRUCTURES */

typedef struct s_cmd
{
	char	*whole_cmd; // echo -n hi there
	char	*cmd_name; // echo
	char	*cmd_path; // init to NULL
	char	**argument; // split de whole_cmd
	int		input_redir; // < = 1; << = 2; else = 0
	char	*input_file;
	int		output_redir; // > = 1; >> = 2; else = 0
	char	*output_file;
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
}	t_arg;

// typedef struct s_cmd
// {
// 	char	*path;
// 	char	**args;
// }	t_cmd;

// typedef struct s_pipex
// {
// 	bool	here_doc;
// 	int		in_fd;
// 	int		out_fd;
// 	t_cmd	*cmd;
// 	size_t	nb_cmd;
// 	char	**paths;
// 	int		pipe_fd[2][2];
// 	int		*pid_child;
// }	t_pipex;

/* FONCTIONS */



#endif
