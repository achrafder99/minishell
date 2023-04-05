/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node_by_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/04/04 22:49:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void delete_node_by_type(t_components **head, char *type) 
{
    t_components *prev;
    t_components *curr;
    
    prev = NULL;
    curr = *head;

    while (curr != NULL && strcmp(curr->type.type, type) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    if (prev == NULL) 
        *head = curr->next;
    else 
        prev->next = curr->next;
    free(curr);
}