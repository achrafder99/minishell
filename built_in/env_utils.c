/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:57:39 by aalami            #+#    #+#             */
/*   Updated: 2023/04/05 18:18:41 by aalami           ###   ########.fr       */
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
	
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
	while (env[i])
	{
			ret[i] = ft_strjoin("declare -x ",env[i]);
		i++;
	}
	ret[i] = NULL;
	exp = sort_env(ret);
	return (exp);
}
t_lst	*creat_list()
{
	t_lst *a;
	a = malloc(sizeof(t_lst));
	a->top = NULL;
	return (a);
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
t_node	*ft_new_node(char *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!(node))
		return (0);
	node->data = strdup(content);
	node->next = NULL;
	return (node);
}
void    push_list(t_lst *lst, char **env)
{
    int i;
    t_node *tmp;
    
    i = 0;
    while (env[i])
    {
        tmp = ft_new_node(env[i]);
        ft_lstadd_back(lst, tmp);
        i++;
    }
}