# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adardour <adardour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 22:38:34 by adardour          #+#    #+#              #
#    Updated: 2023/05/19 00:58:07 by adardour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
EXECUTABLE= minishell

SRCS = main.c minishell.c handle_signals.c cut_string.c is_redirect.c check_is_built_in.c new_string.c \
includes.c \
./restring.c \
./get_argv.c ./utils/join.c ./utils/ft_strcmp.c ./utils/match_file.c ./utils/number_of_file.c \
./utils/split.c ./utils/ft_strchr.c ./utils/ft_strtrim.c ./utils/ft_strlen.c ./utils/get_size.c ./utils/ft_memcpy.c ./utils/ft_strstr.c \
./utils/ft_strdup.c ./utils/number_of_stars.c ./utils/matched_pattern.c ./utils/ft_atoi.c ./utils/ft_itoa.c ./utils/ft_putstr_fd.c ./utils/ft_putchar_fd.c ./utils/ft_isdigit.c ./utils/ft_atoi2.c\
./toknize/push_token.c \
./parse_and_lexer/redirection.c ./parse_and_lexer/redirect_componenets.c ./parse_and_lexer/split_token.c \
./parse_and_lexer/lexer.c ./parse_and_lexer/parser.c ./parse_and_lexer/handle_errors.c ./parse_and_lexer/piped.c ./parse_and_lexer/init_command.c \
./parse_and_lexer/split_input.c ./parse_and_lexer/push_component.c ./parse_and_lexer/lex_redirection.c \
./parse_and_lexer/add_args.c ./parse_and_lexer/open_fd.c ./parse_and_lexer/regex.c ./parse_and_lexer/handle_command.c \
./parse_and_lexer/ft_strtok.c ./parse_and_lexer/split2.c ./parse_and_lexer/expander.c ./parse_and_lexer/extract.c \
./parse_and_lexer/handle_pipe.c \
./built_in/echo.c ./built_in/pwd.c ./built_in/cd.c ./built_in/exit.c ./built_in/env_utils.c ./built_in/export.c ./built_in/ft_env.c ./built_in/unset.c\
./execute/simple_command.c ./execute/execute_built_in.c ./execute/open_file.c ./execute/get_cmd.c \
./execute/start_redirection.c \
./free/free_things.c ./free/free_node.c ./free/free_utils.c \
./check/check_command.c ./check/check_is_space.c ./check/check_quotes.c ./check/check_option.c \
./check/check_redirection.c ./check/check_type.c ./check/is_qouted.c ./check/check_is_type_command.c \
./check/is_wildcard.c \
./execute/execute_pipe.c \
./linked_list/add_front.c ./linked_list/delete_node_by_type.c ./linked_list/creat_list.c \
./heredoc/heredoc_list.c wildcard.c\


CC		= cc -g
RM		= rm -rf
CFLAGS = -Wall -Wextra -Werror -g

OBJS = ${SRCS:%.c=%.o}

all:	${NAME}

%.o:%.c minishell.h
		${CC} -I$(shell brew --prefix readline)/include -c  $< -o ${<:%.c=%.o}
		
$(NAME): ${OBJS} 
		${CC} ${OBJS} -o ${EXECUTABLE} -L$(shell brew --prefix readline)/lib -lreadline
clean:
		${RM}  ${OBJS} 

fclean:	clean
		${RM} ${NAME} 
		rm -rf minishell
		
re:		fclean all