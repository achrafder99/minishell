/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:04:05 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 00:05:13 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_key_with_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;
	int		flag;

	flag = 0;
	if (ft_strchr(split[0], '+'))
	{
		split[0] = ft_strtrim(split[0], "+");
		flag = 1;
	}
	if (if_key_exist(split[0], lst))
		update_value(split, lst, str, flag);
	else
	{
		new = ft_new_node(split[0], get_value(str));
		ft_lstadd_back(lst, new);
	}
}

void	add_key_with_no_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;
	int		flag;

	flag = 0;
	if (ft_strchr(split[0], '+'))
	{
		split[0] = ft_strtrim(split[0], "+");
		flag = 1;
	}
	if (if_key_exist(split[0], lst))
		update_value(split, lst, NULL, flag);
	else
	{
		new = ft_new_node(split[0], "\0");
		ft_lstadd_back(lst, new);
	}
}

void	add_key(t_lst *exp, char *str)
{
	t_node	*new;

	if (!if_key_exist(str, exp))
	{
		new = ft_new_node(str, NULL);
		ft_lstadd_back(exp, new);
	}
}

void	append_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;

	if (if_key_exist(ft_strtrim(split[0], "+"), lst))
		update_value(split, lst, str, 1);
	else
	{
		if (!split[1])
			add_key_with_no_value(lst, str, split);
		else
			add_key_with_value(lst, str, split);
	}
}

int	if_valid_identifier(char **arg, t_env *env)
{
	int		i;
	int		j;
	int		invalid;
	char	**split;
	int		flag;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		invalid = 0;
		split = ft_split(arg[i], '=');
		if (process_key_and_value(env, arg, split, i))
		{
			flag = 1;
			ft_putstr_fd("minshell: export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		free_things(split);
		i++;
	}
	return (flag);
}
