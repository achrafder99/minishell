/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:47:05 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 00:10:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_heredoc(t_command **command, t_components *node)
{
	if ((*command)->heredoc_lst == NULL)
		(*command)->heredoc_lst = creat_heredoc_list();
	ft_add_heredoc((*command)->heredoc_lst, new_heredoc(node->token,
			node->next->token));
	free((*command)->last_in);
	free((*command)->in_type);
	(*command)->last_in = ft_strdup(node->next->token);
	(*command)->in_type = ft_strdup(node->type.type);
}

void	handle_append(t_command **command, int *fd, t_components *node)
{
	free((*command)->last_out);
	free((*command)->out_type);
	(*command)->last_out = cut_string(node->next->token);
	(*command)->out_type = cut_string(node->type.type);
	*fd = open((*command)->last_out, O_CREAT, 0777);
	if (*fd == -1)
	{
		perror("");
		exit(1);
	}
	close(*fd);
}

void	handle_redirect(t_command **command,
						t_components *node,
						int *fd,
						t_info *info)
{
	if (!ft_strcmp(node->type.type, "REDIRECT_in"))
	{
		free((*command)->last_in);
		free((*command)->in_type);
		(*command)->last_in = cut_string(node->next->token);
		(*command)->in_type = cut_string(node->type.type);
		if (open_in(*command) == 1)
		{
			info->status_code = 1;
			return ;
		}
	}
	if (!ft_strcmp(node->type.type, "REDIRECT_out"))
	{
		free((*command)->last_out);
		free((*command)->out_type);
		(*command)->last_out = cut_string(node->next->token);
		(*command)->out_type = cut_string(node->type.type);
		*fd = open((*command)->last_out, O_RDONLY | O_CREAT, 0777);
		if (*fd == -1)
			return (perror(""), exit(1));
		close(*fd);
	}
}
