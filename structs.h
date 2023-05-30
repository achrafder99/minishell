/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:34:29 by adardour          #+#    #+#             */
/*   Updated: 2023/05/30 12:48:48 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "heredoc.h"
# include <stdio.h>

typedef struct s_type
{
	char				*type;
}						t_type;

typedef struct s_regex
{
	char				*pattern;
}						t_regex;

typedef struct s_fds
{
	int					fd_in;
	int					fd_out;
	int					fd_append;
}						t_fds;

typedef struct s_last_file
{
	char				*last_in;
	char				*last_out;
	char				*in_type;
	char				*out_type;
}						t_last_file;

typedef struct s_heredoc
{
	char				*heredoc;
	char				*delimit;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_here_lst
{
	t_heredoc			*top;
}						t_here_lst;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					argc;
	char				*last_in;
	char				*last_out;
	char				*in_type;
	char				*out_type;
	t_here_lst			*heredoc_lst;
	t_here_data			*data_lst;
}						t_command;

typedef struct s_piped
{
	t_command			*command;
	int					number_of_commands;
}						t_piped;

typedef struct s_components
{
	char				*token;
	struct s_components	*next;
	struct s_type		type;
}						t_components;

typedef struct s_rowandcolumn
{
	size_t				words;
	int					i;
	int					j;
	char				**ptr;
	int					nextblock;
	int					length;
}						t_rowsandcolumns;

typedef struct s_data
{
	char				*type;
	t_components		**head;
	char				**spliting;
	int					*i;
	int					*flags;
}						t_data;

typedef struct s_node
{
	char				*key;
	char				*value;
	struct s_node		*next;
}						t_node;

typedef struct s_lst
{
	t_node				*top;
	int					flag;
}						t_lst;
typedef struct s_env
{
	t_lst				*exp;
	t_lst				*env;
	char				**env_arr;
}						t_env;

typedef struct s_info
{
	char				*pwd;
	int					status_code;
	int					flags;
	char				*type;
	char				*token;
	char				**spliting;
	char				*temp;
	t_env				*env;
}						t_info;

#endif