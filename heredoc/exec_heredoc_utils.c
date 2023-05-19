/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:50:13 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 20:13:52 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_here_data *data)
{
	t_here_node	*top;

	top = data->top;
	while (top)
	{
		free(top->data);
		free(top);
		top = top->next;
	}
	free(top);
	free(data);
}

t_here_node	*last_here_node(t_here_data *lst)
{
	t_here_node	*tmp;

	if (lst->top == NULL)
		return (0);
	tmp = lst->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_here_node	*new_here_node(char *data)
{
	t_here_node	*node;

	node = malloc(sizeof(t_here_node));
	if (!(node))
		return (0);
	node->data = ft_strdup(data);
	node->next = NULL;
	return (node);
}

void	ft_add_here_data(t_here_data *lst, t_here_node *new)
{
	t_here_node	*tmp;

	if (!new)
		return ;
	if (!lst->top)
		lst->top = new;
	tmp = last_here_node(lst);
	tmp->next = new;
	new->next = 0;
}

t_here_data	*creat_heredoc_data_list(void)
{
	t_here_data	*lst;

	lst = malloc(sizeof(t_here_lst));
	if (!lst)
		return (0);
	lst->top = NULL;
	return (lst);
}
