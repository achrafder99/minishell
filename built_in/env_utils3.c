/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:48 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 16:57:01 by aalami           ###   ########.fr       */
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
	char	*key;
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
