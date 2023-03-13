/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/03/14 00:19:37 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define MAX_PATH_LENGTH 1024

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

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
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
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_split(char const *s, char c);
void				display_env(char **env);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
void				push(t_tokens **head, char *command);
void				parse(char *input, t_tokens **head, char **env);
void				echo(t_tokens *tokens, char **env);
void				cd(t_tokens *tokens);
void				pwd(t_tokens *tokens);
int					get_size(t_tokens *tokens);
void				exit_shell();

#endif