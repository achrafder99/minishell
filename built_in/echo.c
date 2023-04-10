/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 02:37:12 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_thins(char *word, t_info *info)
{
	if (ft_strchr(word, '$'))
	{
		print_env(word, info);
		write(1, " ", 1);
	}
	else
	{
		ft_put_echo(word);
		write(1, " ", 1);
	}
}

int	echo(t_command *cmd, t_info *info)
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
	while (cmd->args[i])
	{
		printf_thins(cmd->args[i], info);
		i++;
	}
	if (!flags)
		write(1, "\n", 1);
	return (0);
}
