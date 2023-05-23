/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 12:56:20 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_command *cmd)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	if (cmd->argc == 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (cmd->args[i] != NULL && !ft_strcmp(cmd->args[i], "-n"))
	{
		flags = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		write(1, " ", 1);
	}
	if (!flags)
		write(1, "\n", 1);
	return (0);
}
