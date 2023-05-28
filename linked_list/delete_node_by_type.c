/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node_by_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/26 18:59:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_components	*delete_node_by_type(t_components **head, char *type)
{
	t_components	*prev;
	t_components	*curr;
	t_components	*temp;

	prev = NULL;
	curr = *head;
	while (curr != NULL && ft_strcmp(curr->type.type, type) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	temp = curr;
	if (temp == NULL)
		return (NULL);
	if (prev == NULL)
		*head = temp->next;
	else
		prev->next = temp->next;
	return (*head);
}
