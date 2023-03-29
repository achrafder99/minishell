/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 02:48:16 by adardour         ###   ########.fr       */
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
# include "./utils/get_next_line/get_next_line.h"

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

typedef struct t_tokens
{
	char			*token;
	struct t_tokens	*next;
	struct t_type	type;
}					t_tokens;

typedef struct t_rowandcolumn
{
	size_t			words;
	int				i;
	int				j;
	char			**ptr;
	int				nextblock;
	int				length;
}					t_rowsandcolumns;

char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
void				display_env(char **env);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
void				push(t_tokens **head, char *command, char *type);
void				lexer(char *input, t_tokens **head,t_info *info);
void				echo(t_tokens *tokens);
void				cd(t_command *cmd);
void				pwd(t_command *cmd);
int					get_size(t_tokens *tokens);
void				exit_shell(void);
void 				parser(t_tokens *tokens,t_info *info);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
void 				handle_signals(int sign);
char				*cut_string(char *s);
void				simple_command(t_command *command);
void				execute_built_in(t_command *cmd);
char 				**get_argv(t_command *command,int number_arg);
int					is_redirect(t_command *command);
int					check_is_built_in(char *cmd);
char				*new_str(char *str,int count);
int					includes(char car);
int					handle_errors(t_tokens *tokens);
void				free_things(char **spliting);
int					check_command(char *command);
void				execute_pipe(t_piped *pipe);
#endif