/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:30:20 by adardour          #+#    #+#             */
/*   Updated: 2023/05/21 14:20:37 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_component(t_components **head, char **spliting, int *i,
		t_info *info)
{
	if (!ft_strcmp(info->type, "PIPE"))
	{
		push(head, spliting[*i], "PIPE");
		if (spliting[*i + 1] != NULL && !check_is_redirection(spliting[*i + 1])
			&& ft_strcmp(spliting[*i + 1], "|"))
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
			info->flags = 1;
		}
	}
	else if (!ft_strcmp(info->type, "REDIRECT_out"))
		out(spliting, i, head, info);
	else if (!ft_strcmp(info->type, "REDIRECT_in"))
		in(spliting, i, head, info);
	else if (!ft_strcmp(info->type, "APPEND_MODE"))
		append_mode(spliting, i, head, info);
	else if (!ft_strcmp(info->type, "HEREDOC"))
		here_doc(spliting, i, head, info);
}
