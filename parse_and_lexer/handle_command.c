/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:48:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 00:15:17 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_heredoc(t_command **command, int *fd, t_components *node)
{
	if ((*command)->heredoc_lst == NULL)
		(*command)->heredoc_lst = creat_heredoc_list();
	ft_add_heredoc((*command)->heredoc_lst, new_heredoc(node->token, node->next->token));
	(*command)->last->last_in = ft_strdup(node->next->token);
	(*command)->last->in_type = ft_strdup(node->type.type);
}

void	handle_append(t_command **command, int *fd, t_components *node)
{
	(*command)->last->last_out = ft_strdup(node->next->token);
	*fd = open((*command)->last->last_out , O_CREAT, 0777);
	close(*fd);
	(*command)->last->out_type = ft_strdup(node->type.type);
}

void	handle_redirect(t_command **command, \
t_components *node, int *fd, t_info *info)
{
	// if ((*command)->last == NULL)
	// {	printf("33\n");
	// 	(*command)->last = malloc(sizeof(t_last_file));
	// 	(*command)->last->last_in = NULL;
	// 	(*command)->last->last_out = NULL;
	// 	(*command)->last->in_type = NULL;
	// 	(*command)->last->out_type = NULL;
	// }
	if (!ft_strcmp(node->type.type, "REDIRECT_in"))
	{
		(*command)->last->last_in = ft_strdup(node->next->token);
		(*command)->last->in_type = ft_strdup(node->type.type);
		if (open_in(*command, node->next->token) == 1)
		{
			info->status_code = 1;
			return ;
		}
	}
	if (!ft_strcmp(node->type.type, "REDIRECT_out"))
	{
		(*command)->last->last_out = ft_strdup(node->next->token);
		(*command)->last->out_type = ft_strdup(node->type.type);
		*fd = open((*command)->last->last_out ,O_RDONLY | O_CREAT, 0777);
		close(*fd);
	}
	
}

char	*handle_command(t_components *node, t_command **command, t_info *info)
{
	t_last_file	*last;
	char		*cut_str;
	int			fd;
	int flag;

	flag = 0;
	cut_str = cut_string(node->token);
	if (!ft_strcmp(node->type.type, "COMMAND") || !ft_strcmp(node->type.type, "HEREDOC"))
		*command = init_command(*command, cut_str);
	else if (!ft_strcmp(node->type.type, "OPTION") \
		|| !ft_strcmp(node->type.type, "ARG"))
		(*command)->args = add_args(*command, cut_str);
		
	else if (check_type(node->type.type))
	{
		(*command)->last = malloc(sizeof(t_last_file));
		(*command)->last->last_in = NULL;
		(*command)->last->last_out = NULL;
		(*command)->last->in_type = NULL;
		(*command)->last->out_type = NULL;
		if (!ft_strcmp(node->token, "<") || !ft_strcmp(node->token, ">"))
			handle_redirect(command, node, &fd, info);
		if (!ft_strcmp(node->token, ">>"))
			handle_append(command, &fd, node);
		if (!ft_strcmp(node->type.type, "HEREDOC"))
			handler_heredoc(command, &fd, node);
	}
	return ("SUCCESS");
}
