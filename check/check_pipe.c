/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:16:09 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 00:16:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_pipe(t_components *node)
{
	t_components	*temp;

	temp = node;
	while (node)
	{
		if (!ft_strcmp(node->type.type, "PIPE"))
			return (1);
		node = node->next;
	}
	return (0);
}
