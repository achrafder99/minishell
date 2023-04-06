/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:57:24 by adardour          #+#    #+#             */
/*   Updated: 2023/04/06 16:39:47 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_built_in(t_command *cmd, t_lst *env, t_lst *exp){
	
	if(!ft_strcmp(cmd->name,"cd"))
		cd(cmd);
	else if(!ft_strcmp(cmd->name,"pwd"))
		pwd(cmd);
	else if(!ft_strcmp(cmd->name,"echo"))
		echo(cmd);
	else if(!ft_strcmp(cmd->name,"export"))
		ft_export(cmd, exp);
	else if (!ft_strcmp(cmd->name,"env"))
		ft_env(env);
}
