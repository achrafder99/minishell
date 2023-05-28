/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/05/28 14:07:37 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define MAX_PATH_LENGTH 1024

# include "heredoc.h"
# include "structs.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		g_heredoc_flag;

char				*ft_strjoin(char *s1, char *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
void				push(t_components **head, char *command, char *type);
void				lexer(char *input, t_components **head, t_info *info,
						t_env *env);
int					echo(t_command *cmd, t_env *env, t_info *info);
int					cd(t_command *cmd, t_env *env);
int					pwd(void);
int					get_size(t_components *tokens);
int					exit_shell(t_command *cmd);
void				parser(t_components *tokens, t_info *info, t_env *env);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
void				handle_signals(int sign);
char				*cut_string(char *s);
void				simple_command(t_command *command, t_info *info,
						t_env *env);
int					execute_built_in(t_command *cmd, t_info *info, t_env *env);
char				**get_argv(t_command *command, int number_arg);
int					is_redirect(t_command *command);
int					check_is_built_in(char *cmd);
char				*new_str(char *str, int count);
int					includes(char car);
int					handle_errors(t_components *tokens);
void				free_things(char **spliting);
int					check_command(char *command, t_env *env);
void				execute_pipe(t_piped *pipe, t_info *info, t_env *env);
int					check_is_space(char *input);
int					check_quotes(char *input);
size_t				ft_strlen(const char *s);
void				free_node(t_components *head);
int					check_option(t_components *node);
void				in(char **spliting, int *i, t_components **head,
						t_info *info);
void				out(char **spliting, int *i, t_components **head,
						t_info *info);
void				append_mode(char **spliting, int *i, t_components **head,
						t_info *info);
void				here_doc(char **spliting, int *i, t_components **head,
						t_info *info);
void				redirect_componenets(char **spliting, int *i,
						t_components **head, t_info *info);
int					check_is_redirection(char *symbol);
void				piped(t_piped *pipe_line, t_command *command, t_info *info,
						t_env *env);
int					check_type(char *type);
t_command			*init_command(t_command *command, char *str);
int					open_in(t_command *command);
void				ft_lstadd_front(t_components **lst, t_components *new);
t_components		*delete_node_by_type(t_components **head, char *type);
char				*ft_strdup(const char *s1);
int					match_regex(t_regex *regex, const char *input);
t_regex				*compile_regex(const char *pattern);
void				push_component(t_components **head, char **spliting, int *i,
						t_info *info);
void				lex_redirection(t_data *data);
char				*get_cmd(char *command_name, t_env *env, t_info *info);
int					redirection(t_command *cmd, t_here_data *data_lst);
void				handle_command(t_components *node, t_command **command,
						t_info *info);
void				handle_pipe(t_piped **pipe_line, t_command **command);
void				display_error(char *cut_str, t_command *command);
char				**split_input(char *input);
int					check_if_qouted(char *string);
int					check_is_command(t_components *tokens);
int					is_wildcard(char **argv);
int					match_file(char *pattern);
int					number_of_file(char **argv);
int					number_of_star(char **argv);
int					matched_file(char *pattern);
t_lst				*creat_list(void);
t_env				*creat_env(void);
int					ft_export(t_command *cmd, t_env *env);
int					get_env_size(char **env);
t_lst				*get_export_env(char **env);
t_node				*ft_lstlast(t_lst *lst);
void				ft_lstadd_back(t_lst *lst, t_node *new);
t_node				*ft_new_node(char *key, char *value);
char				*get_value(char *str);
void				push_list(t_lst *lst, char **env);
int					ft_env(t_lst *env_lst, t_command *command);
t_lst				*get_env(char **env);
t_lst				*sort_env(char **env);
unsigned long long	ft_atoi2(const char *str);
int					ft_atoi(const char *str);
char				*ft_itoa(int c);
void				run_child(t_command *command, char **argv, t_env *env,
						t_info *info);
void				first_step(t_command *command, t_info *info, int *flags,
						t_env *env);
char				**get_new_env(t_lst *env);
int					get_list_size(t_lst *lst);
int					ft_unset(t_command *cmd, t_env *env);
void				remove_variable(char *key, t_lst *lst);
int					number_of_token(char *string);
char				*extract(char *compo, t_env *env, t_info *info);
void				expander(t_components *node, t_env *env, t_info *info);
int					if_key_exist(char *key, t_lst *lst);
int					number(char *string);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
t_here_lst			*creat_heredoc_list(void);
void				ft_add_heredoc(t_here_lst *lst, t_heredoc *new);
t_heredoc			*last_heredoc(t_here_lst *lst);
t_heredoc			*new_heredoc(char *heredoc, char *delimit);
t_here_data			*open_heredoc(t_here_lst *list, t_info *info);
int					ft_isdigit(int c);
void				free_command(t_command *command);
void				free_data(t_here_data *data);
int					main(int argc, char **argv, char **envp);
void				interrupt_handler(int signal);
void				process_input(char *input, t_env *env, t_info *info);
char				*get_input(void);
char				**split_token(char *str);
int					count_token(char *str);
void				free_components(t_components *head);
void				extract_matched_file(char *pattern, char *type,
						t_components **components1);
int					check_is_matched(char *pattern);
t_components		*insert_at_position(t_components *node);
void				without_command(t_components *node, t_info *info);
t_components		*insert_command_at_front(t_components *tokens);
int					not_pipe(t_components *node);
void				handler_heredoc(t_command **command, t_components *node);
void				handle_append(t_command **command, int *fd,
						t_components *node);
void				handle_redirect(t_command **command,
						t_components *node,
						int *fd,
						t_info *info);
char				**found_args(t_components **node);
void				free_heredoc(t_here_lst *lst_heredoc);
void				free_pipe_line(t_piped *pipe_line);
int					open_fds(const char *type, const char *filename, int *fd);
size_t				ft_strcspn(const char *s1, const char *charset);
char				*ft_strncpy(char *dst, const char *src, size_t len);
void				process_push_redirection(char **spliting,
						t_components **head,
						int i,
						t_info *info);
void				process_push_command(char **spliting, t_components **head,
						int i, t_info *infmao);
int					if_key_exist(char *key, t_lst *lst);
t_node				*find_key_to_update(t_lst *lst, char *key);
void				update_value(char **split, t_lst *lst, char *str, int flag);
int					add_keys_and_values(t_env *env, char *arg, char **split,
						int i);
int					process_key_and_value(t_env *env, char **arg, char **split,
						int i);
void				add_key_with_value(t_lst *lst, char *str, char **split);
void				add_key_with_no_value(t_lst *lst, char **split);
void				add_key(t_env *env, char *str);
void				append_value(t_lst *lst, char *str, char **split);
int					if_valid_identifier(char **arg, t_env *env);
char				*update_shell_level(char *value);
void				set_oldpwd(t_lst *lst);
void				add_new_env_variables(t_lst *env, char **new);
t_here_node			*last_here_node(t_here_data *lst);
t_here_node			*new_here_node(char *data);
void				ft_add_here_data(t_here_data *lst, t_here_node *new);
t_here_data			*creat_heredoc_data_list(void);
void				fill_heredoc(t_heredoc *tmp, int *flag,
						t_here_data *data_lst, t_info *info);
void				handle_command_not_found(t_info *info, t_command *command,
						int *flags);
int					save_and_redirect(t_command *command, int *save_in,
						int *save_out);
void				free_execution_args(char **argv, t_env *env);
void				reset_std_in_out(t_command *command, int save_in,
						int save_out);
int					check_rederict_in(t_command *cmd);
int					check_rederict_out(t_command *cmd);
int					save_heredoc_data(t_here_data *data_lst);
int					**creat_pipes(t_piped *piping);
void				open_pipes(t_piped *piping, int **fd);
void				close_pipes(int **fd);
void				check_command_not_found(int flag, t_info *info, t_env *env,
						char *cmd_name);
void				duplicate_read_write(int i, int **fd, int flag);
void				check_for_heredoc(t_command *command, t_info *info);
void				complete_pipes_ex(int flag, t_command *command,
						t_info *info, t_env *env);
void				wait_for_last_exit(int id, int **fd, t_info *info,
						t_command *command);
int					*allocate_for_ids(t_piped *piping);
void				exec_pipe_commande(t_command *cmd, t_info *info,
						t_env *env);
void				wait_for_exit_state(int id, t_info *info);
int					check_empty_command(char *command, t_info *info, int *flag);
void				hanlde_quite(int signal);
int					open_pipe(t_components **head, t_info *info);
int					check_command_pipe(t_components **head);
void				remove_empty_command(t_components **components);
void				fill(char **str, int i, char **tokens);
char				**allocate_tokens(char *str);
int					count_length_token(char *str);
char				*proccess(t_env *env, t_info *info, char *ss1);
void				handle_env_not_found(t_lst *env_lst);
void				handle_exp_not_found(t_lst *env_lst);
char				**creat_basic_env(void);
void				update_oldpwd(t_lst *lst);
void				update_pwd(t_lst *lst);
void				update_dir(t_env *env, int flag);
char				*extract_value(t_info *info, t_env *env, char *token);
int					check_open_heredocs(t_components *nodes);
#endif