/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/05/12 20:03:33 by aalami           ###   ########.fr       */
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

	tokens = node;
	while (node != NULL)
	{
		if (node->next == NULL)
			break ;
		info->status_code = open_fds(node->type.type, node->next->token, &fd);
		close(fd);
		node = node->next;
	}
}

void	parser(t_components *tokens, t_info *info, t_env *env)
{
	t_components	*node;
	t_command		*command;
	t_piped			*pipe_line;

	node = tokens;
	// while (node)
	// {
	// 	printf("%s\n",node->token);
	// 	node = node->next;
	// }
	// return;

	command = NULL;
	pipe_line = NULL;
	if (ft_strcmp(tokens->token, "exit") && handle_errors(tokens))
		info->status_code = 1;
	if (check_is_command(node) && check_is_redirection(node->token))
		node = insert_command_at_front(tokens);
	if (!check_is_command(node) && check_is_redirection(node->token))
		without_command(node, info);
	else
	{
		while (node != NULL)
		{
			if (ft_strcmp(node->type.type, "PIPE"))
				handle_command(node, &command, info);
			else
				handle_pipe(node, &pipe_line, &command);
			node = node->next;
		}
		if (command != NULL)
			piped(pipe_line, command, info, env);
		command = NULL;
	}
}
