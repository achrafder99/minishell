/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:58:32 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:50:15 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	fill_matched_file(char **argv, int *i, char *pattern)
{
	DIR				*dir;
	t_regex			*regex;
	struct dirent	*entry;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))
		{
			argv[*i] = ft_strdup(entry->d_name);
			(*i)++;
		}
		entry = readdir(dir);
	}
	free(regex);
	free(regex->pattern);
	closedir(dir);
}

void	expand_file(char **argv, t_command *command, int *j, int *i)
{
	if (ft_strstr(command->args[*j], "*") && matched_file(command->args[*j]))
	{
		fill_matched_file(argv, i, (command->args[*j]));
		(*j)++;
	}
	else
	{
		argv[*i] = ft_strdup(command->args[*j]);
		(*i)++;
		(*j)++;
	}
}

char	**init_wildcard(char **argv, t_command *command, \
						int *number_arg, int *full_size)
{
	if (command->name && command->argc == 0)
	{
		argv = malloc(sizeof(char *) * 2);
		argv[0] = command->name;
		argv[1] = NULL;
		return (argv);
	}
	if (is_wildcard(command->args))
		*full_size = ((number_of_file(command->args) + \
		(*number_arg - number_of_star(command->args))) + 1);
	else
		*full_size = command->argc + 2;
	argv = malloc(sizeof(char *) * *full_size + 1);
	return (argv);
}

char	**get_argv(t_command *command, int number_arg)
{
	char			**argv;
	int				full_size;
	int				i;
	int				j;

	full_size = 0;
	argv = init_wildcard(argv, command, &number_arg, &full_size);
	if (!argv)
		return (printf("error\n"), (NULL));
	argv[0] = ft_strdup(command->name);
	i = 1;
	j = 0;
	while (i < full_size)
	{
		if (command->args[j] == NULL)
			break ;
		else
			expand_file(argv, command, &j, &i);
	}
	argv[i] = NULL;
	return (argv);
}
