# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 10:52:24 by zmeribaa          #+#    #+#              #
#    Updated: 2022/05/31 13:16:20 by hbouhsis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= minishell.c \
\
./Parsing/expand_lexer.c \
./Parsing/free.c \
./Parsing/lexer_collect.c \
./Parsing/lexer_utils.c \
./Parsing/lexer_utils2.c \
./Parsing/lexer.c \
./Parsing/mini_utils.c \
./Parsing/parse_redirection.c \
./Parsing/parser_command.c \
./Parsing/parsing.c \
./Parsing/signals.c \
./Parsing/token.c \
\
./execution/builtins/cd_builtin.c \
./execution/builtins/echo_builtin.c \
./execution/builtins/env_builtin.c \
./execution/builtins/exit_builtin.c \
./execution/builtins/export_builtin.c \
./execution/builtins/pwd_builtin.c \
./execution/builtins/unset_builtin.c \
\
./execution/env_utils/env_builder.c \
./execution/env_utils/env_utils.c \
\
./execution/execution_utils/basic_tools.c \
./execution/execution_utils/dup_utils.c \
./execution/execution_utils/error_message.c \
./execution/execution_utils/ft_atoi.c \
./execution/execution_utils/ft_itoa.c \
./execution/execution_utils/ft_split.c \
./execution/execution_utils/ft_strcmp.c \
./execution/execution_utils/ft_strjoin2.c \
./execution/execution_utils/join_3_strings.c \
./execution/execution_utils/printing_tools.c \
\
./execution/execute_builtins.c \
./execution/execute_cmd.c \
./execution/heredoc.c \
./execution/pipeline_execution.c \
./execution/redirection_implementer.c \

NAME 	=	Minishell
CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address
LDFLAGS	=	-L /Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS=	-I /Users/$(USER)/.brew/opt/readline/include
READLINE=	-lreadline $(LDFLAGS) $(CPPFLAGS)
Includes= -I./Includes 

all : $(NAME)

$(NAME):
	@clear
	$(CC)  $(CFLAGS) $(READLINE) $(SRCS) $(Includes) -o $(NAME)
	@echo "\033[0;32mCompiled (｡•̀ᴗ-)✧\033[0m"

clean :
	@echo "\033[0;31mCleaned ʕ ಡ ﹏ ಡ\033[0m"

fclean: clean
	@(rm -rf $(NAME))
	@rm -rf *.dSYM
	@echo "\033[0;31mCleaned ʕ ಡ ﹏ ಡ\033[0m"

re:	fclean all

.PHONY : clean fclean re
