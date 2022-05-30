# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 10:52:24 by zmeribaa          #+#    #+#              #
#    Updated: 2022/05/30 22:21:50 by hbouhsis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	Minishell
CC		= 	cc
SRC		=	./Parsing/*.c minishell.c ./execution/*.c ./execution/execution_utils/*.c ./execution/builtins/*.c 
LIB		= -I./Includes 
FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g -lreadline -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include 

all : $(NAME)

$(NAME):
	@clear
	$(CC) -g $(SRC) $(LIB) $(FLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled (｡•̀ᴗ-)✧\033[0m"

clean :
	@echo "\033[0;31mCleaned ʕ ಡ ﹏ ಡ\033[0m"

fclean: clean
	@(rm -rf $(NAME))
	@rm -rf *.dSYM
	@echo "\033[0;31mCleaned ʕ ಡ ﹏ ಡ\033[0m"

re:	fclean all

.PHONY : clean fclean re
