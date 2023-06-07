/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:42:23 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 01:50:09 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(t_components *node, t_info *info)
{
	char	*error;

	error = "invalid option\n";
	if (check_is_built_in(node->token))
	{
		if (!ft_strcmp(node->token, "cd") && node->next
			&& !ft_strcmp(node->next->type.type, "OPTION")
			&& !ft_strcmp(node->next->token, "-"))
			return (0);
		else if (ft_strcmp(node->token, "echo") && node->next
			&& !ft_strcmp(node->next->type.type, "OPTION"))
		{
			open_h(node, info);
			write(2, error, ft_strlen(error));
			return (1);
		}
	}
	return (0);
}
