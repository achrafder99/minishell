/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:38:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/27 23:57:20 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
