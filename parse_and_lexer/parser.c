/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 23:04:07 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_her(t_components *tokens)
{
	int		fd;
	char	*line;
	char	*deli;

	deli = tokens->next->token;
	fd = open(".heredoc", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		return (perror(""), exit(0));
	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if (!strncmp(line, deli, ft_strlen(deli)))
				break ;
			write(fd, line, ft_strlen(line));
		}
		else
			break ;
		free(line);
		line = NULL;
	}
}

void	without_command(t_components *node, t_info *info)
{
	t_components	*tokens;
	int				fd;

	tokens = node;
	while (tokens != NULL)
	{
		if (tokens->next == NULL)
			break ;
		if (ft_strcmp(tokens->type.type, "HEREDOC"))
		{
			info->status_code = open_fds(tokens->type.type, tokens->next->token,
					&fd);
			close(fd);
		}
		else
			open_her(tokens);
		tokens = tokens->next;
	}
}

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
			handle_pipe(&pipe_line, &command);
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
