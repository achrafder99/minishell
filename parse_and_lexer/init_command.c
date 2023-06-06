/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:41:37 by adardour          #+#    #+#             */
/*   Updated: 2023/06/03 15:27:11 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_command(t_command *command, char *str)
{
	char	*cmd;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
	{
		return (NULL);
		exit(1);
	}
	cmd = cut_string(str);
	command->name = ft_strdup(cmd);
	free(cmd);
	cmd = NULL;
	command->argc = 0;
	command->args = NULL;
	command->heredoc_lst = NULL;
	command->data_lst = NULL;
	command->last_in = NULL;
	command->last_out = NULL;
	command->in_type = NULL;
	command->out_type = NULL;
	return (command);
}
