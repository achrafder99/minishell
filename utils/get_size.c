/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 20:01:57 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size(t_components *tokens)
{
	int				size;
	t_components	*node;

	node = tokens->next;
	size = 0;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}
