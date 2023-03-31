/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:57:24 by adardour          #+#    #+#             */
/*   Updated: 2023/03/31 00:59:25 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_built_in(t_command *cmd){
	if(!ft_strcmp(cmd->name,"cd"))
		cd(cmd);
	else if(!ft_strcmp(cmd->name,"pwd"))
		pwd(cmd);
	// else if(!ft_strcmp(cmd->name,"export"))
	// 	export(cmd);
}
