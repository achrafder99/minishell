/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:48:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 15:01:45 by adardour         ###   ########.fr       */
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

void	handle_command(t_components *node, t_command **command, t_info *info)
{
	t_last_file	*last;
	int			fd;

	if (!ft_strcmp(node->type.type, "COMMAND"))
		*command = init_command(*command, node->token);
	else if (!ft_strcmp(node->type.type, "OPTION") \
		|| !ft_strcmp(node->type.type, "ARG"))
		(*command)->args = add_args(*command, node->token);
	else if (check_type(node->type.type))
	{
		(*command)->last = malloc(sizeof(t_last_file));
		if ((*command)->last == NULL)
		{
			perror("");
			exit(1);
		}
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
}
