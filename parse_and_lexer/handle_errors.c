/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:31:26 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 01:49:13 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_node(t_components *node)
{
	return (node->next != NULL && check_is_redirection(node->token)
		&& ft_strcmp(node->type.type, "PIPE") && !ft_strlen(node->next->token));
}

int	handle_pipe_errors(t_components *node)
{
	static int	track;
	char		*error;

	error = "tsh: syntax error near unexpected token `|'\n";
	if (!ft_strcmp(node->type.type, "PIPE"))
	{
		if (node->next == NULL || (ft_strcmp(node->next->type.type, "COMMAND")
				&& !check_is_redirection(node->next->token)) || track == 0)
		{
			write(2, error, ft_strlen(error));
			return (258);
		}
	}
	track++;
	return (0);
}

int	handle_redirect_errors(t_components *node)
{
	char	*error;

	if (!ft_strcmp(node->type.type, "REDIRECT_in")
		|| !ft_strcmp(node->type.type, "REDIRECT_out")
		|| !ft_strcmp(node->type.type, "APPEND_MODE")
		|| !ft_strcmp(node->type.type, "HEREDOC"))
	{
		if (node->next == NULL || check_is_redirection(node->next->token)
			|| !ft_strcmp(node->next->type.type, "PIPE"))
		{
			error = "tsh: syntax error near unexpected token `newline'\n";
			write(2, error, ft_strlen(error));
			return (258);
		}
	}
	return (0);
}

int	handle_errors(t_components *tokens, t_info *info)
{
	t_components	*node;

	node = tokens;
	if (check_open_heredocs(node))
		exit(2);
	if (check_option(node, info))
		return (1);
	while (node != NULL)
	{
		if (check_node(node))
		{
			open_h(tokens, info);
			return (write(2, "tsh :ambiguous redirect\n", 25), (1));
		}
		if (handle_pipe_errors(node) || handle_redirect_errors(node))
		{
			open_h(tokens, info);
			return (258);
		}
		node = node->next;
	}
	return (0);
}
