/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:11 by adardour          #+#    #+#             */
/*   Updated: 2023/04/14 03:41:27 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_built_in(t_command *cmd, t_info *info, t_env *env)
{
	if (!ft_strcmp(cmd->name, "cd"))
		return (info->status_code = cd(cmd, env));
	else if (!ft_strcmp(cmd->name, "pwd"))
		return (info->status_code = pwd(cmd));
	else if (!ft_strcmp(cmd->name, "echo"))
		return (info->status_code = echo(cmd, info));
	else if (!ft_strcmp(cmd->name, "export"))
		return (info->status_code = ft_export(cmd, env));
	
	return (1);
}
