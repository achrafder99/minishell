/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 12:42:42 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prase_tokens(t_components *node, t_info *info, t_env *env)
{
	t_command	*command;
	t_piped		*pipe_line;

	command = NULL;
	pipe_line = NULL;
	while (node != NULL)
	{
		if (ft_strcmp(node->type.type, "PIPE"))
		{
			if (!ft_strcmp(node->type.type, "COMMAND") && !info->flags)
				info->flags = 1;
			handle_command(node, &command, info);
		}
		else
		{
			handle_pipe(node, &pipe_line, &command);
			info->flags = 0;
			free(command);
			command = NULL;
		}
		node = node->next;
	}
	if (command != NULL)
		piped(pipe_line, command, info, env);
}

void	parser(t_components *tokens, t_info *info, t_env *env)
{
	t_components	*node;

	node = tokens;
	info->flags = 0;
	if (ft_strcmp(tokens->token, "exit") && handle_errors(tokens))
	{
		info->status_code = 1;
		return ;
	}
	if (check_is_command(node) && check_is_redirection(node->token))
		node = insert_command_at_front(tokens);
	if (not_pipe(node))
		node = insert_at_position(node);
	if (!check_is_command(node) && check_is_redirection(node->token))
		without_command(node, info);
	else
		prase_tokens(node, info, env);
}
