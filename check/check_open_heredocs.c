/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:38:13 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 01:36:51 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_h(t_components *node, t_info *info)
{
	t_components	*tokens;

	tokens = node;
	while (tokens != NULL)
	{
		if (tokens->next == NULL)
			break ;
		if (!ft_strcmp(tokens->type.type, "HEREDOC") && g_heredoc_flag != -1)
		{
			if (ft_strcmp(tokens->next->token, "|")
				&& !check_is_redirection(tokens->next->token))
				open_her(tokens, info);
			else
				break ;
		}
		tokens = tokens->next;
	}
}

int	check_open_heredocs(t_components *nodes)
{
	int				count;
	t_components	*temp;

	temp = nodes;
	count = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->type.type, "HEREDOC"))
			count++;
		temp = temp->next;
	}
	if (count >= 17)
	{
		write(2, "tsh: maximum here-document count exceeded\n", 43);
		return (1);
	}
	return (0);
}
