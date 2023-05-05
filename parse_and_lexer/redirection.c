/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 00:55:28 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 21:08:45 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in(char **spliting, int *i, t_components **head)
{
	push(head, spliting[*i], "REDIRECT_in");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
	}
}

void	out(char **spliting, int *i, t_components **head)
{
	push(head, spliting[*i], "REDIRECT_out");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
	}
}

void	append_mode(char **spliting, int *i, t_components **head)
{
	push(head, spliting[*i], "APPEND_MODE");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "FILENAME");
		(*i)++;
	}
}

void	here_doc(char **spliting, int *i, t_components **head)
{
	push(head, spliting[*i], "HEREDOC");
	if (spliting[*i + 1] != NULL)
	{
		push(head, spliting[*i + 1], "END_HEREDOC");
		(*i)++;
	}
}
