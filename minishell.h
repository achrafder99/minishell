/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:02 by adardour          #+#    #+#             */
/*   Updated: 2023/03/10 20:25:04 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_PATH_LENGTH 1024

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct t_rowandcolumn
{
	size_t			words;
	int				i;
	int				j;
	char			**ptr;
	int				nextblock;
	int				length;
}					t_rowsandcolumns;

typedef struct t_value{
    char *value;
} t_value;

typedef struct t_set_env{
    char *key;
    t_value *value;
}   t_env;

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);

#endif