/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/04/06 21:26:50 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define MAX_PATH_LENGTH 1024


#define BLUE "\033[38;2;105;210;231m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

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

typedef struct t_heredoc{
	char *end;
    char *cmd;
	char **args;
}   t_heredoc;


typedef struct t_info{
    char *pwd;
    int status_code;

}   t_info;

typedef struct s_ast_node
{
    char *value;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;


typedef struct t_command
{
    char *name;
    char **args;
    int argc;
    char *infile;
    char *outfile;
	char *append_mode;
	char *heredoc;
	char *end_heredoc;
	t_heredoc *here_doc;
} t_command;

typedef struct t_piped{
	t_command *command;
	int number_of_commands;
}	t_piped;

typedef struct t_type
{
	char			*type;
}					t_type;

typedef struct t_components
{
	char			*token;
	struct t_components	*next;
	struct t_type	type;
}					t_components;

typedef struct t_rowandcolumn
{
	size_t			words;
	int				i;
	int				j;
	char			**ptr;
	int				nextblock;
	int				length;
}					t_rowsandcolumns;

typedef struct s_node
{
    char   *key;
    char   *value;
    struct s_node *next;
}t_node;

typedef struct s_lst
{
    t_node *top;
	int	flag;
}t_lst;

char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
void				display_env(char **env);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
void				push(t_components **head, char *command, char *type);
void				lexer(char *input, t_components **head,t_info *info, t_lst *env, t_lst *exp);
void				echo(t_command *cmd);
void				cd(t_command *cmd);
void				pwd(t_command *cmd);
int					get_size(t_components *tokens);
void				exit_shell(void);
void 				parser(t_components *tokens,t_info *info, t_lst *env, t_lst *exp);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
void 				handle_signals(int sign);
char				*cut_string(char *s);
void				simple_command(t_command *command, t_lst *env, t_lst *exp);
void				execute_built_in(t_command *cmd, t_lst *env, t_lst *exp);
char 				**get_argv(t_command *command,int number_arg);
int					is_redirect(t_command *command);
int					check_is_built_in(char *cmd);
char				*new_str(char *str,int count);
int					includes(char car);
int					handle_errors(t_components *tokens);
void				free_things(char **spliting);
int					check_command(char *command);
void				execute_pipe(t_piped *pipe);
int 				check_is_space(char *input);
int 				check_quotes(char *input);
size_t				ft_strlen(const char *s);
void 				free_node(t_components *head);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int 				check_option(t_components  *node);
void 				in(char **spliting,int *i,t_components **head);
void 				out(char **spliting,int *i,t_components **head);
void 				append_mode(char **spliting,int *i,t_components **head);
void 				here_doc(char **spliting,int *i,t_components **head);
void				redirect_componenets(char** spliting, int* i, t_components** head);
void				push_component(t_components **head, char *type, char **spliting, int *i);
void    push_list(t_lst *lst, char **env);
t_node	*ft_new_node(char *key, char *value);
void	ft_lstadd_back(t_lst *lst, t_node *new);
t_node	*ft_lstlast(t_lst *lst);
t_lst	*creat_list();
t_lst	*get_export_env(char **env);
int	get_env_size(char **env);
void	ft_export(t_command *cmd, t_lst *lst);
t_lst *sort_env(char **env);
void    ft_env(t_lst *env_lst);
t_lst   *get_env(char **env);
t_lst   *get_env(char **env);
char	*get_value(char *str);
#endif