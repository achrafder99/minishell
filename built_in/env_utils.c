/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:57:39 by aalami            #+#    #+#             */
/*   Updated: 2023/05/22 18:02:59 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *str)
{
	int	i;

	i = 0;
	while (str)
	{
		if (str[i] == '=')
			return (str + i + 1);
		i++;
	}
	return (0);
}

char	*update_shell_level(char *value)
{
	int		number;
	char	*new_value;
	char	*get_num;

	number = ft_atoi(value);
	if (number > 999)
	{
		new_value = ft_strdup("1");
		printf("minishell: warning: shell level");
		printf("(%d) too high,resetting to 1\n", number + 1);
	}
	else if (number == 999)
		new_value = ft_strdup("0");
	else if (number < 0)
		new_value = ft_strdup("0");
	else
	{
		get_num = ft_itoa(number + 1);
		new_value = ft_strdup(get_num);
		free(get_num);
	}
	free(value);
	return (new_value);
}

int	check_oldpwd(t_lst *lst)
{
	t_node	*tmp;
	t_node	*tmp_a;
	int		flag;

	flag = 0;
	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD") && flag == 0)
		{
			tmp_a = ft_new_node(tmp->key, tmp->value);
			flag = 1;
			tmp = lst->top;
		}
		else if (!ft_strcmp(tmp->key, "PWD") && flag == 1)
		{
			if (!ft_strcmp(tmp->value, tmp_a->value))
				flag = -1;
		}
		tmp = tmp->next;
	}
	free(tmp_a->key);
	free(tmp_a->value);
	free(tmp_a);
	return (flag);
}

t_node	*get_oldpwd(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	set_oldpwd(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL") && !ft_strcmp(tmp->value, "2"))
			break ;
		tmp = tmp->next;
	}
	if (tmp && check_oldpwd(lst) == -1)
	{
		tmp = get_oldpwd(lst);
		free(tmp->value);
		tmp->value = NULL;
	}
	else if (!get_oldpwd(lst))
	{
		tmp = ft_new_node("OLDPWD", NULL);
		ft_lstadd_back(lst, tmp);
	}
}
