/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:24:40 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 20:54:16 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_is_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if(!ft_strcmp(cmd,"export"))
		return (1);
	else if(!ft_strcmp(cmd,"env"))
		return (1);
	return (0);
}
