# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 17:41:22 by sdemaude          #+#    #+#              #
#    Updated: 2024/04/04 15:06:44 by sdemaude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

CC 			= cc
RM			= rm -f

CFLAGS 		= -Wall -Wextra -Werror -g
CLINKS		= -lreadline

LIBFTDIR	= lib/libft
LIBFT		= $(LIBFTDIR)/libft.a

SRCDIR		= src
SRCFILE		=	check_errors\
				exec_one_cmd\
				executing\
				executing_utils\
				handle_redir\
				handle_var\
				init_list\
				inutils\
				main\
				mod_libft\
				parse_line\
				type\
				builtin_exit\
				# handle_builtins\
				# builtin_cd\
				# builtin_echo\
				# builtin_env\
				# builtin_export\
				# builtin_pwd\
				# builtin_unset\

SRC 		= $(addprefix $(SRCDIR)/,$(addsuffix .c,$(SRCFILE)))

OBJDIR		= obj
OBJ 		= $(addprefix $(OBJDIR)/,$(addsuffix .o,$(SRCFILE)))

all: $(OBJDIR) $(NAME)

$(LIBFT): $(LIBFTDIR)
		make -C $(LIBFTDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(CLINKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFTDIR)
	$(RM) -r $(OBJDIR)

fclean: clean
	make fclean -C $(LIBFTDIR)
	$(RM) $(NAME)

re: fclean all

c: all clean

.PHONY:		all bonus clear clean fclean re c
