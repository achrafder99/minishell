/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 20:28:20 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define MAX_PATH_LENGTH 1024

# define BLUE "\033[38;2;105;210;231m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

# include "structs.h"

char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strcmp(const char *s1, const char *s2);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
void			push(t_components **head, char *command, char *type);
void			lexer(char *input, t_components **head, \
				t_info *info, char **env);
int				echo(t_command *cmd, t_info *info);
int				cd(t_command *cmd);
int				pwd(t_command *cmd);
int				get_size(t_components *tokens);
void			exit_shell(void);
void			parser(t_components *tokens, t_info *info, char **env);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strstr(const char *haystack, const char *needle);
void			handle_signals(int sign);
char			*cut_string(char *s);
void			simple_command(t_command *command, t_info *info, char **env);
int				execute_built_in(t_command *cmd, t_info *info);
char			**get_argv(t_command *command, int number_arg);
int				is_redirect(t_command *command);
int				check_is_built_in(char *cmd);
char			*new_str(char *str, int count);
int				includes(char car);
int				handle_errors(t_components *tokens);
void			free_things(char **spliting);
int				check_command(char *command);
void			execute_pipe(t_piped *pipe);
int				check_is_space(char *input);
int				check_quotes(char *input);
size_t			ft_strlen(const char *s);
void			free_node(t_components *head);
int				check_option(t_components *node);
void			in(char **spliting, int *i, t_components **head);
void			out(char **spliting, int *i, t_components **head);
void			append_mode(char **spliting, int *i, t_components **head);
void			here_doc(char **spliting, int *i, t_components **head);
void			redirect_componenets(char **spliting, \
int *i, t_components **head);
void			push_component(t_components **head, \
char *type, char **spliting, int *i);
int				check_is_redirection(char *symbol);
void			piped(t_piped *pipe_line, t_command \
				*command, t_info *info, char **env);
int				check_type(char *type);
t_command		*init_command(t_command *command, char *cut_str);
char			**add_args(t_command *command, char *cut_str);
int				open_in(t_command *command, char *infile);
void			ft_lstadd_front(t_components **lst, t_components *new);
void			delete_node_by_type(t_components **head, char *type);
char			*ft_strdup(const char *s1);
int				match_regex(t_regex *regex, const char *input);
t_regex			*compile_regex(const char *pattern);
void			push_component(t_components **head, char \
				*type, char **spliting, int *i);
void			lex_redirection(t_data *data);
char			*get_cmd(char *command_name);
void			open_file(t_command *command, t_fds *fds);
void			redirection(char *type, char *filename, t_fds *fds);
char			*handle_command(t_components *node, t_command **command, \
			t_info *info);
void			handle_pipe(t_components *node, \
			t_piped **pipe_line, t_command **command);
void			display_error(char *cut_str, t_command *command);
char			**split_input(char *input);
int				check_if_qouted(char *string);
int				check_is_command(t_components *tokens);
int				is_wildcard(char **argv);
int				match_file(char *pattern);
int				number_of_file(char **argv);
int				number_of_star(char **argv);
int				matched_file(char *pattern);
void			print_env(char *string, t_info *info);
void			ft_put_echo(char *string);
void			open_heredoc(char *end);
#endif