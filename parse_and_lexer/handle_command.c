/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:48:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 12:59:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size_of_args(char **argument)
{
	int	size;

	size = 0;
	while (argument[size])
		size++;
	return (size);
}

void	handle_command(t_components *node, t_command **command, t_info *info)
{
	int			fd;

	if (check_is_redirection(node->token) && !info->flags)
	{
		*command = init_command(*command, node->token);
		info->flags = 1;
	}
	else if (!ft_strcmp(node->type.type, "COMMAND") && info->flags)
	{
		*command = init_command(*command, node->token);
		(*command)->args = found_args(&node, node->token);
		(*command)->argc = get_size_of_args((*command)->args);
	}
	else if (check_type(node->type.type))
	{
		if (!ft_strcmp(node->token, "<") || !ft_strcmp(node->token, ">"))
			handle_redirect(command, node, &fd, info);
		if (!ft_strcmp(node->token, ">>"))
			handle_append(command, &fd, node);
		if (!ft_strcmp(node->type.type, "HEREDOC"))
			handler_heredoc(command, &fd, node);
	}
}
