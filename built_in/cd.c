/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 00:47:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_command *cmd)
{
	char *home_dir;
	if(cmd->argc == 0 || !ft_strcmp(cmd->args[0], "~")){
		home_dir = ft_strjoin("/Users/", getenv("USER"));
		chdir(home_dir);
		return;
	}
	else if(access(cmd->args[0],F_OK) != -1){
		chdir(cmd->args[0]);
		return;
	}
	else{
		write(2, "tsh: ", 6); 
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": no such file or directory", ft_strlen(": no such file or directory"));
		write(2, "\n", 1);
		return;
	}
}