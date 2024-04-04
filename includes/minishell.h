/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:21:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/04 14:28:21 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* LIBFT */

# include "../lib/libft/libft.h"

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
# include <limits.h>

/* DEFINE */

# define GENERAL_ERR 1
# define EXEC_CMD_KO 126
# define INVALID_CMD 127
# define TMP_FILE "/tmp/tmp"

/* ENUM */

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_INFILE,
	TOKEN_HEREDOC,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_PIPE
}	t_token;

/* STRUCT */

typedef struct s_cmd		t_cmd;
typedef struct s_tmp_list	t_tmp_list;

typedef struct s_cmd
{
	char	*cmd_path; // init to NULL
	char	**arguments;
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

typedef struct s_tmp_list
{
	char		*content;
	t_token		token;
	t_tmp_list	*next;
}	t_tmp_list;

typedef struct s_arg
{
	int			exit_code; // init to 0
	char		*prompt;
	char		*whole_line;
	char		**arg_tab;
	char		**envp;
	char		**paths;
	t_tmp_list	*lexing;
	int			nb_cmd;
	t_cmd		*cmd_list;
	int			pipe_fd[2][2];
}	t_arg;

/* FONCTIONS */

//GET LINE, PARSE AND INIT TAB (PARSE_LINE)
void		shift_str(char *str, int len);
bool		parse_line(t_arg *arg);

//PROMPT NAME AND MORE (INUTILS)
char		*find_str(char **envp, char *to_find, int skip);
char		*get_prompt(char **envp);
int			count_token(t_tmp_list *lexing, t_token token);

//CHECK FOR SPECIAL CHAR (TYPE)
bool		ft_isspace(char c);
bool		ft_isseparator(char c);
bool		ft_ismetachar(char c);
bool		ft_islong(char *s);

//CHECK FOR INVALID CHAR IN LINE (CHECK_ERRORS)
bool		check_pipe_errors(char *str);
bool		check_redir_errors(char *str);
bool		check_errors(t_arg *arg, char *str);
void		in_quotes(char c, int *state);

//MODIFIED LIBFT FUNCTIONS (MOD_LIBFT)
char		*mod_strdup(char *s, int len);
t_tmp_list	*mod_lstnew(char *content);
void		mod_lstadd_back(t_tmp_list **lst, t_tmp_list *new);
void		mod_strcat(char *dest, char *src);

//REPLACE ENVIRONEMENT VARIABLES (HANDLE_VAR)
int			replace_env_var(t_arg *arg, t_tmp_list **list, int state, int i);

//CREATE COMMAND LINKED LIST (INIT_LIST)
void		init_cmd_list(t_arg *arg, t_cmd **cmd, t_tmp_list *tmp);

// Executing
void		executing(t_arg *param);
//  handle_redirections
int			nb_redir(t_cmd *cmd);
void		read_input(int tmp_fd, char *lim_lr);
int			open_hd(t_cmd *cmd, int i);
int			handle_redir_input(t_cmd *cmd);
int			handle_redir_output(t_cmd *cmd);
//  handle_builtins
int			isbuiltins(t_arg *arg);
int			handle_builtins(t_arg *arg, int builtin_code);
//  one_command
int			exec_one_cmd(t_arg *arg);
int			handle_one_cmd(t_arg *arg);
//  utils
char		*ft_strjoin_path(char *path, char *cmd);
char		*ft_which(char **paths, char *cmd);

// BUILTINS
void		free_tab(char **tab);
void		free_lst(t_tmp_list *lst);
void		free_cmd_lst(t_cmd *lst);
void		builtin_exit(t_arg *arg, bool builtin);

#endif
