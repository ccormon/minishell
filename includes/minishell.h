/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:21:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/04/14 16:13:43 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**************** LIBFT ****************/

# include "../lib/libft/libft.h"

/************** INCLUDES ***************/

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
# include <errno.h>

/*************** DEFINE ****************/

# define GENERAL_ERR 1
# define BUILTIN_KO 2
# define EXEC_CMD_KO 126
# define INVALID_CMD 127
# define CTRL_C 130
# define TMP_FILE "/tmp/tmp"

/**************** ENUM *****************/

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_INFILE,
	TOKEN_HEREDOC,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_PIPE
}	t_token;

/*************** GLOBAL ****************/

extern int					g_here_doc_fd;
extern int					g_signal;

/*************** STRUCT ****************/

typedef struct s_cmd		t_cmd;
typedef struct s_tmp_list	t_tmp_list;

typedef struct s_cmd
{
	char	*cmd_path; // init to NULL
	char	**argv;
	int		status;
	int		pid_child;
	int		*input_redir; // init to NULL; > = 1; << = 2;
	char	**input_file; // init to NULL
	int		input_fd;
	int		*output_redir; // init to NULL; > = 1; >> = 2;
	char	**output_file; // init to NULL
	int		output_fd;
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
	int			exit_code;
	char		*prompt;
	char		*pwd;
	char		*whole_line;
	char		**envp;
	char		**paths;
	t_tmp_list	*lexing;
	int			nb_cmd;
	t_cmd		*cmd_list;
	int			pipe_fd[2];
	int			cmd_read_fd;
}	t_arg;

/************** FONCTIONS **************/

//ENTRY POINT OF THE PROGRAM (FETCH_LINE)
int			fetch_line(char **envp);

//HANDLE SIGNALS (SIGNAL)
void		handle_signal_rl(int sig);
void		handle_signal_cmd(int sig);
void		handle_signal_hd(int sig);
void		change_signal(int param);
void		sig_exit_code(t_arg *arg);

//PROMPT NAME AND MORE (INUTILS)
char		*find_str(char **envp, char *to_find, int skip);
char		*get_prompt(char **envp);
int			count_token(t_tmp_list *lexing, t_token token);

//MODIFIED LIBFT FUNCTIONS (MOD_LIBFT)
char		*mod_strdup(char *s, int len);
t_tmp_list	*mod_lstnew(char *content);
void		mod_lstadd_back(t_tmp_list **lst, t_tmp_list *new);
void		mod_strcat(char *dest, char *src);

//GET LINE, PARSE AND INIT TAB (PARSE_LINE)
void		shift_str(char *str, int len);
bool		parse_line(t_arg *arg);

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

//REPLACE ENVIRONEMENT VARIABLES (HANDLE_VAR)
int		replace_env_var(t_arg *arg, t_tmp_list **list, int state, int i);

//CREATE COMMAND LINKED LIST (INIT_LIST)
void		init_cmd_list(t_arg *arg, t_cmd **cmd, t_tmp_list *tmp);

//EXECUTE ONE OR MORE COMMAND (EXECUTING)
void		executing(t_arg *arg);

//(EXECUTING_UTILS)
char		*ft_strjoin_path(char *path, char *cmd);
char		*ft_which(char **paths, char *cmd);
int		nb_cmd(t_cmd *cmd);
void		exec_errors(t_arg *arg, t_cmd *cmd);
bool		found_path_line(char *str);
char		**found_path(char **envp);

//(EXEC_ONE_CMD)
void		exec_one_cmd(t_arg *arg, t_cmd *cmd);
void		handle_one_cmd(t_arg *arg);

//(EXEC_MULTI_CMD)
void		ft_pipe(t_arg *arg, t_cmd *cmd);
void		exec_cmd(t_arg *arg, t_cmd *cmd);
void		wait_childs(t_arg *arg, t_cmd *cmd, int nb_cmd);
void		handle_multi_cmd(t_arg *arg, t_cmd *cmd);
void		exit_fork(t_arg *arg, int exit_code);

//(HANDLE_REDIR)
int			open_hd(t_cmd *cmd, int i);
int			handle_redir_input(t_cmd *cmd);
int			handle_redir_output(t_cmd *cmd);
bool		handle_redir(t_cmd *cmd);

//(HANDLE_REDIR_UTILS)
int			nb_redir_input(t_cmd *cmd);
int			nb_redir_output(t_cmd *cmd);
void		read_input(int tmp_fd, char *lim_lr);

//(HANDLE_BUILTINS)
bool		ft_isbuiltin(t_cmd *cmd);
bool		handle_builtins(t_arg *arg, t_cmd *cmd, int output_fd);

/************** BUILTINS ***************/

//EXIT (BUILTIN_EXIT)
void		free_tab(char **tab);
void		free_lst(t_tmp_list *lst);
void		free_cmd_lst(t_cmd *lst);
void		builtin_exit(t_arg *arg, char **argv, bool builtin);

//(BUILTIN_ECHO)
void		builtin_echo(t_arg *arg, char **argv, int fd);

//(BUILTIN_PWD)
void		builtin_pwd(t_arg *arg, int fd);

//(BULTIN_CD)
void		builtin_cd(t_arg *arg, char **argv);

//(BUILTIN_ENV)
void		builtin_env(t_arg *arg, char **argv, int fd);

//(BUILTIN_EXPORT)
void		rewrite_evar(t_arg *arg, char *name, char *content);
void		builtin_export(t_arg *arg, char **argv, int fd);

//(BUILTIN_UNSET)
void		builtin_unset(t_arg *arg, char **argv);

//(BUILTIN_UTILS)
char		**find_var(char **envp, char *to_find);

#endif
