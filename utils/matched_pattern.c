/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matched_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:17:43 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:51:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	matched_file(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	t_regex			*regex;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	free(regex);
	free(regex->pattern);
	closedir(dir);
	return (0);
}
