/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node_by_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/29 21:26:30 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_components	*delete_node_by_type(t_components *head, int position)
{
	t_components	*curr;
	t_components	*temp;
	t_components	*components;
	int				current_pos;

	curr = head;
	components = NULL;
	current_pos = 0;
	while (curr != NULL && current_pos != position)
	{
		current_pos++;
		curr = curr->next;
	}
	push(&components, curr->token, curr->type.type);
	temp = head;
	current_pos = 0;
	while (temp != NULL)
	{
		if (current_pos != position)
			push(&components, temp->token, temp->type.type);
		current_pos++;
		temp = temp->next;
	}
	return (components);
}
