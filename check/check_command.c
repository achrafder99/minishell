/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 18:44:58 by aalami           ###   ########.fr       */
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

int	check_command(char *command, t_env *env)
{
	char	*path;

	path = get_path(env->env);
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
