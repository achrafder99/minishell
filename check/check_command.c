/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:40:26 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 02:40:38 by adardour         ###   ########.fr       */
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
	while (spliting[i] != NULL)
	{
		full_command = ft_strjoin(spliting[i],ft_strjoin("/",command));
		if(!access(full_command,X_OK)){
			free_things(spliting);
			spliting = NULL;
			free(full_command);
			full_command = NULL;
			return (1);
		}
		i++;
	}
	free_things(spliting);
	free(full_command);
	spliting = NULL;
	return (0);
}