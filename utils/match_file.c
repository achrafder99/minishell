/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:10:16 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:12:46 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_file(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	t_regex			*regex;
	int				count;

	count = 0;
	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}
