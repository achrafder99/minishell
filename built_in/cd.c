/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 05:50:41 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(t_command *cmd)
{
	char	*home_dir;

	if (cmd->argc == 0 || !ft_strcmp(cmd->args[0], "~"))
	{
		home_dir = ft_strjoin("/Users/", getenv("USER"));
		chdir(home_dir);
		free(home_dir);
		return (0);
	}
	else if (access(cmd->args[0], F_OK) != -1)
		return (chdir(cmd->args[0]), 0);
	else
	{
		write(2, "tsh: ", 6);
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": no such file or directory", \
		ft_strlen(": no such file or directory"));
		write(2, "\n", 1);
		return (1);
	}
	return (1);
}
