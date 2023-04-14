/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:34:29 by adardour          #+#    #+#             */
/*   Updated: 2023/04/11 23:41:00 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_info
{
	char				*pwd;
	int					status_code;
}						t_info;

typedef struct s_last_file
{
	char				*last_file;
	char				*type;
}						t_last_file;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					argc;
	char				*infile;
	char				*outfile;
	char				*append_mode;
	char				*heredoc;
	char				*end_heredoc;
	t_last_file			*last;
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
}						t_env;

#endif