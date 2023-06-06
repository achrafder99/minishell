/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_front.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:47:39 by adardour          #+#    #+#             */
/*   Updated: 2023/05/31 13:35:05 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_components	*createnode(char *token, char *type)
{
	t_components	*new_node;

	new_node = (t_components *)malloc(sizeof(t_components));
	if (new_node == NULL)
	{
		perror("");
		exit(1);
	}
	new_node->token = ft_strdup(token);
	new_node->type.type = ft_strdup(type);
	new_node->next = NULL;
	return (new_node);
}

void	addnodetofront(t_components **head, char *token, char *type)
{
	t_components	*new_node;

	new_node = (t_components *)malloc(sizeof(t_components));
	if (new_node == NULL)
	{
		perror("");
		exit(1);
	}
	new_node->token = token;
	new_node->type.type = type;
	new_node->next = *head;
	*head = new_node;
}
