/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:13:36 by sdemaude          #+#    #+#             */
/*   Updated: 2024/04/02 18:29:10 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "unistd.h"
# include "signal.h"
# include "stdio.h"
# include "stdbool.h"
# include "stdlib.h"
# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd		t_cmd;
typedef struct s_tmp_list	t_tmp_list;

typedef enum e_token
{
	TOKEN_WORD,
	TOKEN_INFILE,
	TOKEN_HEREDOC,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_PIPE
}	t_token;

typedef struct s_cmd
{
	char	*cmd_path; //NULL -> exec
	int		status; //exec
	int		pid_child; //exec
	char	**argument; //echo; -n; hi; there
	int		*input_redir; //< = 1; << = 2; else = 0
	char	**input_file;
	int		*output_redir; //> = 1; >> = 2; else = 0
	char	**output_file;
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
	int			exit_code;
	char		*prompt;
	char		*whole_line;
	char		**envp;
	char		**paths;
	t_tmp_list	*lexing;
	t_cmd		*cmd_list;
	int			pipe_fd[2][2];
}	t_arg;

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

// TMP FREE AND EXIT
void		free_tab(char **tab);
void		free_lst(t_tmp_list *lst);
void		free_cmd_lst(t_cmd *lst);
void		ft_exit(t_arg *arg);

#endif
