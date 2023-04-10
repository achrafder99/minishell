/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 07:05:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	from_path(char *path, char *command)
{
	char	*full_command;
	char	*join;

	full_command = NULL;
	join = ft_strjoin("/", command);
	full_command = ft_strjoin(path, join);
	if (!access(full_command, X_OK))
	{
		free(full_command);
		free(join);
		return (1);
	}
	free(full_command);
	free(join);
	return (0);
}

int	check_command(char *command)
{
	char	*path;
	char	**spliting;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (1);
	}
	spliting = ft_split(path, ':');
	while (spliting[i] != NULL)
	{
		if (from_path(spliting[i], command))
		{
			free_things(spliting);
			return (1);
		}
		i++;
	}
	free_things(spliting);
	return (0);
}
