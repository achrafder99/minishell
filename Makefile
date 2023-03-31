# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 22:38:34 by adardour          #+#    #+#              #
#    Updated: 2023/03/30 17:58:22 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
NC=\033[0m

NAME = minishell
EXECUTABLE= minishell

SRCS = minishell.c handle_signals.c cut_string.c is_redirect.c check_is_built_in.c new_string.c \
includes.c \
./get_argv.c ./utils/join.c  ./utils/ft_strcmp.c \
./utils/split.c ./utils/display_env.c ./utils/ft_strchr.c ./utils/ft_strtrim.c ./utils/ft_strlen.c ./utils/get_size.c ./utils/ft_memcpy.c ./utils/ft_strstr.c \
./toknize/push_token.c \
./parse_and_lexer/lexer.c ./parse_and_lexer/parser.c ./parse_and_lexer/handle_errors.c \
./built_in/echo.c ./built_in/pwd.c ./built_in/cd.c ./built_in/exit.c \
./execute/simple_command.c ./execute/execute_built_in.c \
./free/free_things.c ./free/free_node.c \
./check/check_command.c ./check/check_is_space.c ./check/check_quotes.c \
./execute/execute_pipe.c

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