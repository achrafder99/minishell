/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:38:41 by adardour          #+#    #+#             */
/*   Updated: 2023/05/21 16:09:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_data *data)
{
	t_components	**head;
	char			**spliting;
	int				*i;
	int				*flags;

	head = data->head;
	spliting = data->spliting;
	i = data->i;
	flags = data->flags;
	push(head, spliting[0], "HEREDOC");
	*i = 1;
	if (spliting[1] != NULL && !check_is_redirection(spliting[1]))
	{
		push(head, spliting[1], "END_HEREDOC");
		*i += 1;
		if (spliting[2] != NULL && !check_is_redirection(spliting[2]))
		{
			push(head, spliting[2], "COMMAND");
			*i += 1;
			*flags = 1;
		}
	}
}

void	handle_redirect_out(t_data *data)
{
	t_components	**head;
	char			**spliting;
	int				*i;
	int				*flags;

	head = data->head;
	spliting = data->spliting;
	i = data->i;
	flags = data->flags;
	push(head, spliting[0], "REDIRECT_out");
	*i = 1;
	if (spliting[1] != NULL && !check_is_redirection(spliting[1]))
	{
		push(head, spliting[1], "FILENAME");
		*i += 1;
		if (spliting[2] != NULL && !check_is_redirection(spliting[2]))
		{
			push(head, spliting[2], "COMMAND");
			*i += 1;
			*flags = 1;
		}
	}
}

void	handle_redirect_in(t_data *data)
{
	t_components	**head;
	char			**spliting;
	int				*i;
	int				*flags;

	head = data->head;
	spliting = data->spliting;
	i = data->i;
	flags = data->flags;
	push(head, data->spliting[0], "REDIRECT_in");
	*i = 1;
	if (spliting[1] != NULL && !check_is_redirection(spliting[1]))
	{
		push(head, spliting[1], "FILENAME");
		*i += 1;
		if (spliting[2] != NULL && !check_is_redirection(spliting[2]))
		{
			push(head, spliting[2], "COMMAND");
			*i += 1;
			*flags = 1;
		}
	}
}

void	handle_append_mode(t_data *data)
{
	t_components	**head;
	char			**spliting;
	int				*i;
	int				*flags;

	head = data->head;
	spliting = data->spliting;
	i = data->i;
	flags = data->flags;
	push(head, spliting[0], "APPEND_MODE");
	*i = 1;
	if (spliting[1] != NULL && !check_is_redirection(spliting[1]))
	{
		push(head, spliting[1], "FILENAME");
		*i += 1;
		if (spliting[2] != NULL && !check_is_redirection(spliting[2]))
		{
			push(head, spliting[2], "COMMAND");
			*i += 1;
			*flags = 1;
		}
	}
}

void	lex_redirection(t_data *data)
{
	t_components	**head;
	char			*type;
	char			**spliting;
	int				*i;
	int				*flags;

	type = data->type;
	head = data->head;
	spliting = data->spliting;
	i = data->i;
	flags = data->flags;
	if (!ft_strcmp(type, "<<"))
		handle_heredoc(data);
	else if (!ft_strcmp(type, ">"))
		handle_redirect_out(data);
	else if (!ft_strcmp(type, "<"))
		handle_redirect_in(data);
	else
		handle_append_mode(data);
}
