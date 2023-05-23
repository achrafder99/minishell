/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:12:21 by adardour          #+#    #+#             */
/*   Updated: 2023/05/21 14:12:38 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command_pipe(t_components **head)
{
	t_components	*node;

	node = *head;
	while (node)
	{
		if (node->next == NULL)
			break ;
		if (!ft_strcmp(node->type.type, "PIPE")
			&& !ft_strcmp(node->next->type.type, "PIPE"))
			return (1);
		node = node->next;
	}
	return (0);
}
