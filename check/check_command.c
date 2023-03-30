/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/03/30 01:58:39 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_command(char *command){
	
	char *path;
	path = getenv("PATH");
	char **spliting;
	char *full_command;
	spliting = ft_split(path,':');
	int i;
	i = 0;
	char *join;
	join = ft_strjoin("/",command);
	while (spliting[i] != NULL)
	{
		full_command = ft_strjoin(spliting[i],join);
		if(!access(full_command,X_OK)){
			free_things(spliting);
			free(full_command);
			free(join);
			return (1);
		}
		free(full_command);
		i++;
	}
	free_things(spliting);
	free(full_command);
	free(join);
	return (0);
}