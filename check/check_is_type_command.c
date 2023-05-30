/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_type_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:54:59 by adardour          #+#    #+#             */
/*   Updated: 2023/05/31 00:29:03 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_command(t_components *tokens)
{
	t_components	*node;

	node = tokens;
	while (node)
	{
		if (!ft_strcmp(node->type.type, "COMMAND"))
			return (1);
		node = node->next;
	}
	return (0);
}
