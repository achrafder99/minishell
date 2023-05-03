/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:48:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/03 18:30:57 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_append(t_command **command, int *fd, t_components *node)
{
	(*command)->append_mode = node->next->token;
	*fd = open((*command)->append_mode, O_CREAT, 0777);
	close(*fd);
	(*command)->last->last_file = ft_strdup(node->next->token);
	(*command)->last->type = ft_strdup(node->type.type);
}

void	handle_redirect(t_command **command, \
t_components *node, int *fd, t_info *info)
{
	if ((*command)->last == NULL)
	{
		(*command)->last = malloc(sizeof(t_last_file));
		(*command)->last->last_file = NULL;
		(*command)->last->type = NULL;
	}
	if (!ft_strcmp(node->type.type, "REDIRECT_in"))
	{
		if (open_in(*command, node->next->token) == 1)
		{
			info->status_code = 1;
			return ;
		}
		(*command)->last->last_file = ft_strdup(node->next->token);
		(*command)->last->type = ft_strdup(node->type.type);
	}
	if (!ft_strcmp(node->type.type, "REDIRECT_out"))
	{
		(*command)->outfile = cut_string(node->next->token);
		*fd = open((*command)->outfile, O_RDONLY | O_CREAT, 0777);
		close(*fd);
		(*command)->last->last_file = ft_strdup(node->next->token);
		(*command)->last->type = ft_strdup(node->type.type);
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
	if (!ft_strcmp(node->type.type, "COMMAND"))
		*command = init_command(*command, cut_str);
	else if (!ft_strcmp(node->type.type, "OPTION") \
		|| !ft_strcmp(node->type.type, "ARG"))
		(*command)->args = add_args(*command, cut_str);
	else if (check_type(node->type.type))
	{
		if (ft_strcmp(node->token, "<") || ft_strcmp(node->token, ">"))
			handle_redirect(command, node, &fd, info);
		if (!ft_strcmp(node->token, ">>"))
			handle_append(command, &fd, node);
		if (!ft_strcmp(node->type.type, "HEREDOC"))
		{
			(*command)->heredoc = cut_str;
			(*command)->end_heredoc = ft_strdup(node->next->token);
		}
	}
	return ("SUCCESS");
}
