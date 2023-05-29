/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:17:11 by adardour          #+#    #+#             */
/*   Updated: 2023/05/25 22:35:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char *command_name, t_env *env, t_info *info)
{
	char	**spliting;
	int		i;
	char	*cmd;
	char	*join;

	if (ft_strchr(command_name, '/'))
		return (command_name);
	spliting = ft_split(extract_value(info, env, "PATH"), ':');
	i = 0;
	while (spliting[i] != NULL)
	{
		join = ft_strjoin("/", command_name);
		cmd = ft_strjoin(spliting[i], join);
		if (access(cmd, X_OK) == 0)
		{
			free(join);
			join = NULL;
			return (cmd);
		}
		i++;
	}
	free(join);
	free_things(spliting);
	return (cmd);
}
