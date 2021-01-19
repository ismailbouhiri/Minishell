# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 11:10:10 by ibouhiri          #+#    #+#              #
#    Updated: 2020/12/13 12:18:25 by ibouhiri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	Utils/get_next_line_utils.c \
		Utils/get_next_line.c \
		minishell.c \
		Parsing/ft_var_env.c \
		Parsing/ft_lst.c \
		Parsing/ft_norm.c \
		Parsing/ft_separation.c \
		Parsing/ft_fichier_parser.c \
		Parsing/ft_replace_dollar.c \
		Parsing/export_erreur.c \
		Parsing/ft_check_slash.c \
		Parsing/ft_erreurs.c \
		Parsing/ft_directions.c \
		Parsing/ft_tools.c \
		Execution/first.c \
		Execution/second.c \
		Execution/echo.c \
		Execution/export.c \
		Execution/execute01.c \
		Execution/execute02.c \
		Execution/execute03.c \
		Execution/execute04.c \
		Execution/utils01.c \
		Execution/utils02.c \
		Execution/utils03.c \
		Execution/exit.c \

FLAGE = -Wall -Wextra -Werror

NAME = minishell

all : $(NAME)

$(NAME) : $(SRC)
	gcc $(FLAGE) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
fclean :
	rm -rf $(NAME)

re : clean all