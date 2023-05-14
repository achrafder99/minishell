/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:17:35 by aalami            #+#    #+#             */
/*   Updated: 2023/05/14 15:04:02 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_heredoc	*new_heredoc(char *heredoc, char *delimit)
{
	t_heredoc	*node;

	node = malloc(sizeof(t_heredoc));
	if (!(node))
		return (0);
	node->heredoc = ft_strdup(heredoc);
	node->delimit = ft_strdup(delimit);
	node->next = NULL;
	return (node);
}

t_heredoc	*last_heredoc(t_here_lst *lst)
{
	t_heredoc	*tmp;

	if (lst->top == NULL)
		return (0);
	tmp = lst->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_heredoc(t_here_lst *lst, t_heredoc *new)
{
	t_heredoc	*tmp;
	if (!new)
		return ;
	if (!lst->top)
		lst->top = new;
	tmp = last_heredoc(lst);
	tmp->next = new;
	new->next = 0;
}

t_here_lst	*creat_heredoc_list()
{
	t_here_lst	*lst;
	lst = malloc(sizeof(t_here_lst));
	if (!lst)
		return 0;
	lst->top = NULL;
	return (lst);
}