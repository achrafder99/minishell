/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:01:20 by adardour          #+#    #+#             */
/*   Updated: 2023/05/18 23:14:38 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push(t_components **head, char *command, char *type_command)
{
	t_components	*new_node;
	t_components	*current_node;

	new_node = (t_components *)malloc(sizeof(t_components));
	if (new_node == NULL)
	{
		write(2, "Memory allocation failed\n", 25);
		exit(EXIT_FAILURE);
	}
	new_node->token = ft_strdup(command);
	new_node->type.type = ft_strdup(type_command);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current_node = *head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
}
