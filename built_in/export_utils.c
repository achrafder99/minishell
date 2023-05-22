/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:57:16 by aalami            #+#    #+#             */
/*   Updated: 2023/05/20 23:18:26 by adardour         ###   ########.fr       */
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

	if (flag)
		split[0] = ft_strtrim(split[0], "+");
	tmp = find_key_to_update(lst, split[0]);
	if (str && flag)
	{
		if (tmp->value)
			tmp->value = ft_strjoin(tmp->value, get_value(str));
		else
			tmp->value = ft_strjoin("", get_value(str));
	}
	else if (str && !flag)
	{
		free(tmp->value);
		tmp->value = ft_strdup(get_value(str));
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup("\0");
	}
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
		add_key(env->exp, arg);
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
