/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:11 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 21:56:39 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_built_in(t_command *cmd, t_info *info)
{
	if (!ft_strcmp(cmd->name, "cd"))
		return (info->status_code = cd(cmd));
	else if (!ft_strcmp(cmd->name, "pwd"))
		return (info->status_code = pwd(cmd));
	else if (!ft_strcmp(cmd->name, "echo"))
		return (info->status_code = echo(cmd, info));
	return (1);
}
