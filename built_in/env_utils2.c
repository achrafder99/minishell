/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:32:37 by aalami            #+#    #+#             */
/*   Updated: 2023/05/23 15:58:53 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exp_not_found(t_lst *env_lst)
{
	char	**env;

	env = creat_basic_env();
	if (!env)
		return ;
	push_list(env_lst, env);
	free_things(env);
}

t_lst	*get_export_env(char **env)
{
	char	**ret;
	t_lst	*exp;
	int		i;

	if (env[0] != NULL && env != NULL)
	{
		i = -1;
		ret = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
		if (!ret)
			return (0);
		while (env[++i])
			ret[i] = ft_strdup(env[i]);
		ret[i] = NULL;
		exp = sort_env(ret);
		exp->flag = 0;
		free_things(ret);
	}
	else
	{
		exp = creat_list();
		handle_exp_not_found(exp);
	}
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
