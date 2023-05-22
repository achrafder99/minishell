/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:12:24 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 23:12:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_limit(long long nbr)
{
	if (nbr <= LLONG_MAX && nbr >= LLONG_MIN)
		return (1);
	return (0);
}

int	check_if_numeric_arg(char *arg, long long nbr)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		i = 1;
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

int	handle_single_arg(t_command *cmd)
{
	long long	nbr;
	int			ret;

	ret = 0;
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

int	handle_multiple_args(void)
{
	write(2, "minishell: exit: too many arguments", 35);
	write(2, "\n", 1);
	return (1);
}

int	exit_shell(t_command *cmd)
{
	int			ret;

	ret = 0;
	write(2, "exit\n", 5);
	if (cmd->argc == 1)
		return (handle_single_arg(cmd));
	else if (cmd->argc > 1)
		return (handle_multiple_args());
	else
		return (0);
}
