/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:01:20 by adardour          #+#    #+#             */
/*   Updated: 2023/03/16 19:54:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push(t_tokens **head, char *command,char *type_command)
{
	t_tokens	*new_node;
	t_tokens	*current_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_node->token = strdup(command);
	new_node->type.type = strdup(type_command);
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
