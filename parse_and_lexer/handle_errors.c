/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:31:26 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 12:58:32 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_error(char *cut_str, t_command *command)
{
	char	*error;

	error = ft_strjoin(cut_str, " :command not found\n");
	write(2, error, ft_strlen(error));
	free(error);
	free(command);
	free(cut_str);
}

int	handle_pipe_errors(t_components *node)
{
	char	*error;

	if (node == NULL)
		return (0);
	if (!ft_strcmp(node->type.type, "PIPE"))
	{
		if (node->next == NULL || (!ft_strcmp(node->next->token, "|")))
		{
			error = "parse error: Pipe must be followed by Command\n";
			write(2, error, ft_strlen(error));
			return (1);
		}
		if (ft_strcmp(node->next->type.type, "COMMAND")
			&& !check_is_redirection(node->next->token))
		{
			error = "parse error: Pipe must be followed by Command\n";
			write(2, error, ft_strlen(error));
			return (1);
		}
	}
	return (0);
}

int	handle_redirect_errors(t_components *node)
{
	char	*error;

	if (node == NULL)
		return (0);
	if (!ft_strcmp(node->type.type, "REDIRECT_in")
		|| !ft_strcmp(node->type.type, "REDIRECT_out")
		|| !ft_strcmp(node->type.type, "APPEND_MODE")
		|| !ft_strcmp(node->type.type, "HEREDOC"))
	{
		if (node->next == NULL)
		{
			error = "tsh: syntax error near unexpected token `newline'\n";
			write(2, error, ft_strlen(error));
			return (1);
		}
	}
	return (0);
}

int	handle_errors(t_components *tokens)
{
	t_components	*node;

	node = tokens;
	if (check_option(node))
		return (1);
	while (node != NULL)
	{
		if (ft_strchr(node->token, '\\'))
		{
			write(2, "error\n", 6);
			return (1);
		}
		if (handle_pipe_errors(node))
			return (1);
		if (handle_redirect_errors(node))
			return (1);
		node = node->next;
	}
	return (0);
}
