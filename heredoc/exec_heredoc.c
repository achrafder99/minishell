/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:52:17 by aalami            #+#    #+#             */
/*   Updated: 2023/05/26 19:21:51 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_last_heredoc(t_here_node *node, char *data, int *flag,
		t_here_data *data_lst)
{
	if (*flag)
	{
		node = new_here_node(data);
		ft_add_here_data(data_lst, node);
	}
}

void	fill_heredoc(t_heredoc *tmp, int *flag, t_here_data *data_lst,
		t_info *info)
{
	t_here_node	*node;
	char		*data;
	int			fd;

	node = NULL;
	fd = dup(STDIN_FILENO);
	g_heredoc_flag = 1;
	while (1)
	{
		data = readline(">");
		if (!data || g_heredoc_flag == -1)
		{
			dup2(fd, STDIN_FILENO);
			info->status_code = 1;
			break ;
		}
		if (ft_strcmp(data, tmp->delimit))
			fill_last_heredoc(node, data, flag, data_lst);
		else
			return (free(data));
		free(data);
	}
}

t_here_data	*open_heredoc(t_here_lst *list, t_info *info)
{
	t_heredoc	*tmp;
	t_here_data	*data_lst;
	int			flag;

	tmp = list->top;
	flag = 0;
	data_lst = NULL;
	while (tmp && g_heredoc_flag != -1)
	{
		if (!tmp->next)
		{
			data_lst = creat_heredoc_data_list();
			flag = 1;
		}
		fill_heredoc(tmp, &flag, data_lst, info);
		tmp = tmp->next;
	}
	return (data_lst);
}
