/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:09:25 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 13:15:45 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_components *head)
{
	t_components	*node;
	t_components	*next;

	node = head;
	while (node != NULL)
	{
		next = node->next;
		free(node->token);
		free(node->type.type);
		free(node);
		node = next;
	}
}
