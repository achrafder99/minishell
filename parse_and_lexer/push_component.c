/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:30:20 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 21:08:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_component(t_components **head, char *type, char **spliting, int *i)
{
	if (!ft_strcmp(type, "PIPE"))
	{
		push(head, spliting[*i], "PIPE");
		if (spliting[*i + 1] != NULL)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
		}
	}
	else if (!ft_strcmp(type, "REDIRECT_out"))
		out(spliting, i, head);
	else if (!ft_strcmp(type, "REDIRECT_in"))
		in(spliting, i, head);
	else if (!ft_strcmp(type, "APPEND_MODE"))
		append_mode(spliting, i, head);
	else if (!ft_strcmp(type, "HEREDOC"))
		here_doc(spliting, i, head);
}