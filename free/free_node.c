/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:09:25 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 22:00:12 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_node(t_components *head)
{
	t_components *node = head;
	while (node != NULL)
	{
		t_components *next = node->next;
		free(node->token);
		free(node->type.type);
		free(node);
		node = next;
	}
}