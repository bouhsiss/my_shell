# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 10:52:24 by zmeribaa          #+#    #+#              #
#    Updated: 2022/05/16 17:15:17 by hbouhsis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	Minishell
CC		= 	cc
SRC		=	./Parsing/*.c minishell.c ./execution/*.c
LIB		= -I./Includes 
FLAGS	= -Wall -Wextra -Werror -g -lreadline -fsanitize=address

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
