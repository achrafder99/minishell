/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:52:17 by aalami            #+#    #+#             */
/*   Updated: 2023/05/20 23:30:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_heredoc(t_heredoc *tmp, int *flag, t_here_data *data_lst)
{
	t_here_node	*node;
	char		*data;

	while (1)
	{
		data = readline(">");
		if (!data)
			break ;
		if (ft_strcmp(data, tmp->delimit))
		{
			if (*flag)
			{
				node = new_here_node(data);
				ft_add_here_data(data_lst, node);
			}
		}
		else
		{
			free(data);
			break ;
		}
		free(data);
	}
}

t_here_data	*open_heredoc(t_here_lst *list)
{
	t_heredoc	*tmp;
	t_here_data	*data_lst;
	int			flag;

	tmp = list->top;
	flag = 0;
	data_lst = NULL;
	while (tmp)
	{
		if (!tmp->next)
		{
			data_lst = creat_heredoc_data_list();
			flag = 1;
		}
		fill_heredoc(tmp, &flag, data_lst);
		tmp = tmp->next;
	}
	return (data_lst);
}
