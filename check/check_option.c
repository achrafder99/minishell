/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:42:23 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 21:42:51 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(t_components *node)
{
	char	*error;

	error = "invalid option\n";
	if (check_is_built_in(node->token))
	{
		if (!ft_strcmp(node->token, "echo") \
		&& node->next \
		&& !ft_strcmp(node->next->type.type, "OPTION"))
		{
			write(2, error, ft_strlen(error));
			return (1);
		}
		else if (ft_strcmp(node->token, "echo") \
		&& node->next \
		&& !ft_strcmp(node->next->type.type, "OPTION"))
		{
			write(2, error, ft_strlen(error));
			return (1);
		}
	}
	return (0);
}
