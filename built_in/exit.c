/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:12:24 by adardour          #+#    #+#             */
/*   Updated: 2023/05/12 21:39:59 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_limit(unsigned long long nbr)
{
	if (nbr <= LLONG_MAX )
	{
		return (1);
		
	}
		return (0);
	
}
int	check_if_numeric_arg(char *arg, unsigned long long nbr)
{
	int i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (!check_limit(nbr))
		return (0);
	return (1);
}

int	exit_shell(t_command *cmd)
{
	unsigned char status;
	unsigned long long	nbr;
	int	ret;

	ret = 0;
	write(1, "exit\n", 5);
	if ( cmd->argc == 1)
	{
		nbr = ft_atoi2(cmd->args[0]);
		if (!check_if_numeric_arg(cmd->args[0], nbr))
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": numeric argument required", 28);
			write(2, "\n", 1);
			return (255);
		}
		else
		{
			ret = (unsigned char)nbr;
			return (ret);
		}
	}
	else if (cmd->argc > 1)
	{
		write(2, "minishell: exit: too many arguments", 35);
		write(2, "\n", 1);
		return (1);
	}
	else
		return (0);
}
