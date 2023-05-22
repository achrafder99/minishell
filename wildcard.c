/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:56:52 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 01:01:00 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_matched(char *pattern)
{
	int				flag;
	DIR				*dir;
	t_regex			*regex;
	struct dirent	*entry;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	flag = 0;
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))
			return (free(regex), free(regex->pattern), closedir(dir), 1);
		entry = readdir(dir);
	}
	return (free(regex), free(regex->pattern), closedir(dir), 0);
}

void	extract_matched_file(char *pattern, char *type,
		t_components **components1)
{
	int				flag;
	DIR				*dir;
	t_regex			*regex;
	struct dirent	*entry;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	flag = 0;
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))
		{
			if (!flag)
			{
				push(components1, entry->d_name, type);
				flag = 1;
			}
			else
				push(components1, entry->d_name, "ARG");
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (free(regex), free(regex->pattern));
}
