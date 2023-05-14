/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 00:55:28 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 15:44:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in(char **spliting, int *i, t_components **head, t_info *info)
{
	push(head, spliting[*i], "REDIRECT_in");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
		if (spliting[*i + 1] != NULL \
		&& ft_strcmp(spliting[*i + 1], "|") \
		&& !check_is_redirection(spliting[*i + 1]) \
		&& !info->flags)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
			info->flags = 1;
		}
	}
}

void	out(char **spliting, int *i, t_components **head, t_info *info)
{
	push(head, spliting[*i], "REDIRECT_out");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
		if (spliting[*i + 1] != NULL \
		&& ft_strcmp(spliting[*i + 1], "|") \
		&& !check_is_redirection(spliting[*i + 1]) \
		&& !info->flags)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
			info->flags = 1;
		}
	}
}

void	append_mode(char **spliting, int *i, t_components **head, t_info *info)
{
	push(head, spliting[*i], "APPEND_MODE");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
		if (spliting[*i + 1] != NULL \
		&& ft_strcmp(spliting[*i + 1], "|") \
		&& !check_is_redirection(spliting[*i + 1]) \
		&& !info->flags)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
			info->flags = 1;
		}
	}
}

void	here_doc(char **spliting, int *i, t_components **head, t_info *info)
{
	push(head, spliting[*i], "HEREDOC");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "END_HEREDOC");
		(*i)++;
		if (spliting[*i + 1] != NULL \
		&& ft_strcmp(spliting[*i + 1], "|") \
		&& !check_is_redirection(spliting[*i + 1]) \
		&& !info->flags)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
			info->flags = 1;
		}
	}
}
