/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 15:09:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_fds(const char *type, const char *filename, int *fd)
{
	if (!ft_strcmp(type, "REDIRECT_out"))
	{
		*fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
			return (perror("error occurred."), -1);
		write(*fd, "", 1);
	}
	else if (!ft_strcmp(type, "REDIRECT_in"))
	{
		*fd = open(filename, O_RDWR | O_TRUNC, 0644);
		if (*fd == -1)
		{	
			printf("tsh: %s: No such file or directory\n", filename);
			return (1);
		}
	}
	else if (!ft_strcmp(type, "APPEND_MODE"))
	{
		*fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
			return (perror("error occurred."), -1);
	}
	else if (!ft_strcmp(type, "HEREDOC"))
	{	
		printf("open heredoc\n");
	}
	return (0);
}

t_components	*insert_command_at_front(t_components *tokens)
{
	t_components	*goal;
	t_components	*temp;

	if (tokens == NULL)
	{
		tokens = temp;
		return (NULL);
	}
	goal = tokens;
	while (goal != NULL && ft_strcmp(goal->type.type, "COMMAND") != 0)
	goal = goal->next;
	if (goal != NULL)
	{
		temp = goal;
		delete_node_by_type(&tokens, "COMMAND");
		ft_lstadd_front(&tokens, temp);
	}
	return (tokens);
}

void	without_command(t_components *node, t_info *info)
{
	t_components	*tokens;
	int				fd;
	char			*line;
	char			*deli;
	int			temppp;

	tokens = node;
	while (tokens != NULL)
	{
		if (tokens->next == NULL)
			break;
		if (ft_strcmp(tokens->type.type, "HEREDOC"))
		{
			info->status_code = open_fds(tokens->type.type, tokens->next->token, &fd);
			close(fd);
		}
		else{
			deli = tokens->next->token;
			while (1)
			{
				line = readline("> ");
				if (!strncmp(line, deli, ft_strlen(line)))
					break ;
			}
			free(line);
		}
		tokens = tokens->next;
	}
}

int	not_pipe(t_components *node)
{
	t_components *temp;
	temp = node;
	while (node)
	{
		if (!ft_strcmp(node->type.type,"PIPE"))
			return (1);
		node = node->next;
	}
	return (0);
}

void	parser(t_components *tokens, t_info *info, t_env *env)
{
	t_components	*node;
	t_command		*command;
	t_piped			*pipe_line;

	node = tokens;
	command = NULL;
	pipe_line = NULL;
	if (ft_strcmp(tokens->token, "exit") && handle_errors(tokens))
		info->status_code = 1;
	if (check_is_command(node) && \
	check_is_redirection(node->token) \
	&& !not_pipe(node))
		node = insert_command_at_front(tokens);
	if (!check_is_command(node) && check_is_redirection(node->token))
		without_command(node, info);
	else
	{
		while (node != NULL)
		{
			printf("Token (%s) Type (%s)\n",node->token,node->type.type);
			// if (ft_strcmp(node->type.type, "PIPE"))
			// 	handle_command(node, &command, info);
			// else
			// 	handle_pipe(node, &pipe_line, &command);
			node = node->next;
		}
		if (command != NULL)
			piped(pipe_line, command, info, env);
		command = NULL;
	}
}
