# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 22:38:34 by adardour          #+#    #+#              #
#    Updated: 2023/04/09 22:20:38 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
EXECUTABLE= minishell

SRCS = minishell.c handle_signals.c cut_string.c is_redirect.c check_is_built_in.c new_string.c \
includes.c \
./get_argv.c ./utils/join.c ./utils/ft_strcmp.c ./utils/match_file.c ./utils/number_of_file.c \
./utils/split.c ./utils/ft_strchr.c ./utils/ft_strtrim.c ./utils/ft_strlen.c ./utils/get_size.c ./utils/ft_memcpy.c ./utils/ft_strstr.c \
./utils/ft_strdup.c ./utils/number_of_stars.c ./utils/matched_pattern.c \
./toknize/push_token.c \
./parse_and_lexer/redirection.c ./parse_and_lexer/redirect_componenets.c \
./parse_and_lexer/lexer.c ./parse_and_lexer/parser.c ./parse_and_lexer/handle_errors.c ./parse_and_lexer/piped.c ./parse_and_lexer/init_command.c \
./parse_and_lexer/split_input.c ./parse_and_lexer/push_component.c ./parse_and_lexer/lex_redirection.c \
./parse_and_lexer/add_args.c ./parse_and_lexer/open_fd.c ./parse_and_lexer/regex.c ./parse_and_lexer/handle_command.c \
./parse_and_lexer/handle_pipe.c \
./built_in/echo.c ./built_in/pwd.c ./built_in/cd.c ./built_in/exit.c \
./execute/simple_command.c ./execute/execute_built_in.c ./execute/open_file.c ./execute/get_cmd.c \
./execute/start_redirection.c \
./free/free_things.c ./free/free_node.c \
./check/check_command.c ./check/check_is_space.c ./check/check_quotes.c ./check/check_option.c \
./check/check_redirection.c ./check/check_type.c ./check/is_qouted.c ./check/check_is_type_command.c \
./check/is_wildcard.c \
./execute/execute_pipe.c \
./linked_list/add_front.c ./linked_list/delete_node_by_type.c

CC		= cc
RM		= rm -rf
CFLAGS = -Wall -Wextra -Werror -g

OBJS = ${SRCS:%.c=%.o}

all:	${NAME}

%.o:%.c minishell.h
		${CC} -c $< -o ${<:%.c=%.o} 
		
$(NAME): ${OBJS} 
		${CC} ${OBJS} -o ${EXECUTABLE} -lreadline

clean:
		${RM}  ${OBJS} 

fclean:	clean
		${RM} ${NAME} 
		rm -rf minishell
		
re:		fclean all