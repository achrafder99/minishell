/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:57:16 by aalami            #+#    #+#             */
/*   Updated: 2023/05/25 18:01:51 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_key_exist(char *key, t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_node	*find_key_to_update(t_lst *lst, char *key)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	update_value(char **split, t_lst *lst, char *str, int flag)
{
	t_node	*tmp;
	char	*save;

	if (flag)
	{
		save = split[0];
		split[0] = ft_strtrim(split[0], "+");
		free (save);
	}
	tmp = find_key_to_update(lst, split[0]);
	save = tmp->value;
	if (str && flag)
	{
		if (tmp->value)
			tmp->value = ft_strjoin(tmp->value, get_value(str));
		else
			tmp->value = ft_strjoin("", get_value(str));
	}
	else if (str && !flag)
		tmp->value = ft_strdup(get_value(str));
	else
		tmp->value = ft_strdup("\0");
	free (save);
}

int	add_keys_and_values(t_env *env, char *arg, char **split, int i)
{
	if (arg[i] == '=' && i != 0)
	{
		if (arg[i + 1])
		{
			add_key_with_value(env->exp, arg, split);
			add_key_with_value(env->env, arg, split);
		}
		else
		{
			add_key_with_no_value(env->exp, split);
			add_key_with_no_value(env->env, split);
		}
	}
	else if (arg[i] == '+' && arg[i + 1] == '=' && i != 0)
	{
		append_value(env->exp, arg, split);
		append_value(env->env, arg, split);
	}
	else if (arg[i] == '\0')
		add_key(env, arg);
	else
		return (1);
	return (0);
}

int	process_key_and_value(t_env *env, char **arg, char **split, int i)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	while (arg[i][j])
	{
		while ((arg[i][j] && arg[i][j] >= 95 && arg[i][j] <= 122)
			|| (arg[i][j] >= 65 && arg[i][j] <= 90))
			j++;
		if (add_keys_and_values(env, arg[i], split, j))
			ret = 1;
		break ;
		j++;
	}
	return (ret);
}
