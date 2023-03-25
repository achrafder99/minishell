# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 22:38:34 by adardour          #+#    #+#              #
#    Updated: 2023/03/23 22:38:35 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
NC=\033[0m

NAME = minishell
EXECUTABLE= minishell

SRCS = minishell.c ./utils/join.c ./utils/ft_strlen.c ./utils/ft_strcmp.c \
./utils/split.c ./utils/display_env.c ./utils/ft_strchr.c ./utils/ft_strtrim.c ./utils/get_size.c \
./toknize/push_token.c \
./parse_and_lexer/lexer.c ./parse_and_lexer/parser.c\
./built_in/echo.c ./built_in/pwd.c ./built_in/cd.c ./built_in/exit.c

CC		= cc
RM		= rm -rf
CFLAGS = -Wall -Wextra -Werror -g

OBJS = ${SRCS:%.c=%.o}

all:	${NAME}

%.o:%.c minishell.h
		@${CC} -c $< -o ${<:%.c=%.o} 
		
$(NAME): ${OBJS} 
		@${CC} ${OBJS} -o ${EXECUTABLE} -lreadline

clean:
		@${RM}  ${OBJS} 

fclean:	clean
		@${RM} ${NAME} 
		@rm -rf minishell
		
re:		fclean all