/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:09:25 by adardour          #+#    #+#             */
/*   Updated: 2023/03/30 01:05:40 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_node(t_components *head){
    t_components *node;
    node = head;
    while (node != NULL)
    {
        free(node->token);
        free(node->type.type);
        free(node);
        node->token = NULL;
        node->type.type = NULL;
        node = node->next;
    }
    free(node);
    node = NULL;
}