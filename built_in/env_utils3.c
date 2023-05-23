/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:48 by aalami            #+#    #+#             */
/*   Updated: 2023/05/23 17:25:44 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_list_size(t_lst *lst)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = lst->top;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	add_new_env_variables(t_lst *env, char **new)
{
	t_node	*tmp;
	char	*key;
	int		i;

	i = 0;
	tmp = env->top;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			new[i] = ft_strjoin(key, tmp->value);
		else
			new[i] = ft_strdup(key);
		free(key);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
}

char	**get_new_env(t_lst *env)
{
	char	**new;
	t_node	*tmp;
	int		size;

	size = get_list_size(env);
	tmp = env->top;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
	{
		write(2, "error\n", 6);
		exit(1);
	}
	add_new_env_variables(env, new);
	return (new);
}

char	**creat_basic_env(void)
{
	char	**env;
	char	*wd;

	env = (char **)malloc(sizeof(char *) * 5);
	wd = malloc(sizeof(char) * MAX_PATH_LENGTH);
	if (!env && !wd)
		return (0);
	wd = getcwd(wd, MAX_PATH_LENGTH);
	env[0] = ft_strjoin("OLDPWD=", wd);
	env[1] = ft_strjoin("PWD=", wd);
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	free(wd);
	return (env);
}

void	handle_env_not_found(t_lst *env_lst)
{
	char	**env;

	env = creat_basic_env();
	if (!env)
		return ;
	push_list(env_lst, env);
	free_things(env);
}
