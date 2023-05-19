/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:57:39 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 14:04:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
t_lst	*get_export_env(char **env)
{
	char	**ret;
	t_lst	*exp;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!ret)
		return (0);
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	exp = sort_env(ret);
	exp->flag = 0;
	free_things(ret);
	return (exp);
}

t_node	*ft_lstlast(t_lst *lst)
{
	t_node	*tmp;

	if (lst->top == NULL)
		return (0);
	tmp = lst->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
void	ft_lstadd_back(t_lst *lst, t_node *new)
{
	t_node	*tmp;

	if (!new)
		return ;
	if (!lst->top)
		lst->top = new;
	tmp = ft_lstlast(lst);
	tmp->next = new;
	new->next = 0;
}

t_node	*ft_new_node(char *key, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!(node))
		return (0);
	node->key = strdup(key);
	if (!value)
		node->value = NULL;
	else
		node->value = strdup(value);
	node->next = NULL;
	return (node);
}

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
		printf("minishell: warning: shell level (%d) too high,resetting to 1\n",
				number + 1);
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

	tmp_a = NULL;
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
	// printf("%d\n", flag);
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

void	push_list(t_lst *lst, char **env)
{
	int i;
	t_node *tmp;
	char **split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!ft_strcmp(split[0], "SHLVL"))
			split[1] = update_shell_level(split[1]);
		if (split[2])
			tmp = ft_new_node(split[0], get_value(env[i]));
		else
			tmp = ft_new_node(split[0], split[1]);
		ft_lstadd_back(lst, tmp);
		free_things(split);
		i++;
	}
	set_oldpwd(lst);
}