/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:11 by adardour          #+#    #+#             */
/*   Updated: 2023/06/02 22:17:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_built_in(t_command *cmd, t_info *info, t_env *env)
{
	if (!ft_strcmp(cmd->name, "cd"))
		return (info->status_code = cd(cmd, env));
	else if (!ft_strcmp(cmd->name, "pwd"))
		return (info->status_code = pwd());
	else if (!ft_strcmp(cmd->name, "echo"))
		return (info->status_code = echo(cmd, env, info));
	else if (!ft_strcmp(cmd->name, "export"))
		return (info->status_code = ft_export(cmd, env));
	else if (!ft_strcmp(cmd->name, "unset"))
		return (info->status_code = ft_unset(cmd, env));
	else if (!ft_strcmp(cmd->name, "env"))
		return (info->status_code = ft_env(env->env, cmd));
	else if (!ft_strcmp(cmd->name, "exit"))
	{
		info->status_code = exit_shell(cmd);
		if (info->status_code != 1)
			exit(info->status_code);
	}
	return (1);
}
