/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 23:08:02 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_dir(char *command)
{
	struct stat	filestat;

	if (stat(command, &filestat) == 0)
	{
		if (S_ISDIR(filestat.st_mode))
			return (1);
	}
	return (0);
}

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

char	*get_path(t_lst *env)
{
	t_node	*tmp;

	tmp = env->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_path(char *path, char *command)
{
	int		i;
	char	**spliting;

	i = 0;
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

int	check_command(char *command, t_env *env, t_info *info)
{
	char	*path;

	(void)info;
	path = get_path(env->env);
	if (check_is_dir(command) || ft_strlen(command) == 0)
		return (0);
	if (ft_strstr(command, "./") == NULL)
	{
		if (!path && !check_is_built_in(command))
			return (0);
	}
	if (!check_is_built_in(command))
	{
		if (ft_strchr(command, '/'))
		{
			if (access(command, X_OK) == 0)
				return (1);
		}
		if (check_path(path, command))
			return (1);
	}
	else
		return (1);
	return (0);
}
