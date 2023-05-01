/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/05/01 17:18:04 by aalami           ###   ########.fr       */
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
	t_node *tmp;
	
	tmp = env->top;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return(tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
int	check_command(char *command, t_env *env)
{
	char	*path;
	char	**spliting;
	int		i;

	i = 0;
	path = get_path(env->env);
	if (!path)
		return (0);
	char **mini = ft_split(command,'/');
	// printf("dd == %s\n",strrchr(command,'/'));
	if (!check_is_built_in(command))
	{
		if (ft_strchr(command, '/'))
		{
			if (access(command, X_OK) == 0)
				return (1);
		}
		spliting = ft_split(path, ':');
		while (spliting[i] != NULL)
		{
			if (from_path(spliting[i], command))
				return (1);
			i++;
		}
	}
	else
		return (1);
	free_things(spliting);
	return (0);
}
