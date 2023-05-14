/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:30:20 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 15:10:16 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_component(t_components **head, char *type, char **spliting, int *i,t_info *info)
{
	if (!ft_strcmp(type, "PIPE"))
	{
		push(head, spliting[*i], "PIPE");
		if (spliting[*i + 1] != NULL \
		&& ft_strcmp(spliting[*i + 1], "<<") \
		&& ft_strcmp(spliting[*i + 1], ">>") \
		&& ft_strcmp(spliting[*i + 1], "<") \
		&& ft_strcmp(spliting[*i + 1], ">")) \
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
		}
	}
	else if (!ft_strcmp(type, "REDIRECT_out"))
		out(spliting, i, head,info);
	else if (!ft_strcmp(type, "REDIRECT_in"))
		in(spliting, i, head,info);
	else if (!ft_strcmp(type, "APPEND_MODE"))
		append_mode(spliting, i, head,info);
	else if (!ft_strcmp(type, "HEREDOC"))
		here_doc(spliting, i, head, info);
}
