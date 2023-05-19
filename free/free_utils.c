/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:39:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 00:40:10 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_components(t_components *head)
{
	t_components	*current;
	t_components	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current->type.type);
		free(current);
		current = next;
	}
}
