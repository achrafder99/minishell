/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/05/29 21:25:21 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_her(t_components *tokens, t_info *info)
{
	int		fd;
	char	*line;
	char	*deli;

	deli = tokens->next->token;
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (perror("dup"));
	g_heredoc_flag = 1;
	while (1)
	{
		line = readline("> ");
		if (!line || g_heredoc_flag == -1)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("dup");
			info->status_code = 1;
			break ;
		}
		else if (!ft_strcmp(line, deli))
			return (free(line));
		free(line);
	}
}

void	without_command(t_components *node, t_info *info)
{
	t_components	*tokens;
	int				fd;
	char			*clear_file_name;

	tokens = node;
	while (tokens != NULL)
	{
		if (tokens->next == NULL)
			break ;
		if (!ft_strcmp(tokens->type.type, "APPEND_MODE")
			|| !ft_strcmp(tokens->type.type, "REDIRECT_out")
			|| !ft_strcmp(tokens->type.type, "REDIRECT_in"))
		{
			clear_file_name = cut_string(tokens->next->token);
			info->status_code = open_fds(tokens->type.type, clear_file_name,
					&fd);
			close(fd);
			free(clear_file_name);
		}
		else if (!ft_strcmp(tokens->type.type, "HEREDOC") \
		&& g_heredoc_flag != -1)
			open_her(tokens, info);
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
	int				exit_status;
	int				flag;

	node = tokens;
	info->flags = 0;
	flag = 0;
	exit_status = handle_errors(tokens);
	if (ft_strcmp(tokens->token, "exit") && exit_status)
		return ;
	if (check_is_command(node) && check_is_redirection(node->token))
	{
		flag = 1;
		node = insert_command_at_front(tokens);
	}
	if (not_pipe(node))
		node = insert_at_position(node);
	if (!check_is_command(node) && check_is_redirection(node->token))
		without_command(node, info);
	else
		prase_tokens(node, info, env);
	if (flag)
		free_components(node);
}
