/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:57:39 by aalami            #+#    #+#             */
/*   Updated: 2023/04/14 05:42:44 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
t_lst	*get_export_env(char **env)
{
	char **ret;
	t_lst	*exp;
	int i;
	// printf("dd\n");
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
	while (env[i])
	{
			ret[i] = strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	exp = sort_env(ret);
	exp->flag = 0;
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
	int i;

	i = 0;
	while(str)
	{
		if (str[i] == '=')
			return (str + i + 1);
		i++;
	}
	return (0);
}
char	*update_shell_level(char *value)
{
	int number;
	char	*new_value;
	number = ft_atoi(value);
	// printf("%zu %d %s\n",ft_strlen(value), number, value);
	if (number > 999)
	{
		new_value = ft_strdup("1");
		printf("bash: warning: shell level (%d) too high, resetting to 1\n", number + 1);
	}
	else if (number == 999)
		new_value = ft_strdup("0");
	else if (number < 0)
		new_value = ft_strdup("0");
	else
		new_value = ft_strdup(ft_itoa(number + 1));
	return (new_value);
}
void    push_list(t_lst *lst, char **env)
{
    int i;
    t_node *tmp;
	char **split;
    
    i = 0;
    while (env[i])
    {
		split = ft_split(env[i],'=');
		if (!ft_strcmp(split[0], "SHLVL"))
			split[1] = update_shell_level(split[1]);
		if (split[2])
      	tmp = ft_new_node(split[0], get_value(env[i]));
		else
			tmp = ft_new_node(split[0], split[1]);
      ft_lstadd_back(lst, tmp);
      i++;
    }
}