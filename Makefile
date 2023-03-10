# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 17:26:12 by adardour          #+#    #+#              #
#    Updated: 2023/03/10 18:41:48 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
NC=\033[0m

NAME = minishell
EXECUTABLE= minishell

SRCS = minishell.c ./utils/join.c ./utils/ft_strlen.c ./utils/ft_strcmp.c \
./utils/split.c

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