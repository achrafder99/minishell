/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:41:37 by adardour          #+#    #+#             */
/*   Updated: 2023/05/11 20:32:46 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_command(t_command *command, char *cut_str)
{
	command = (t_command *) malloc(sizeof(t_command));
	// command->last = (t_last_file *) malloc(sizeof(t_last_file));
	if (!command)
	{
		return (NULL);
		exit(1);
	}
	command->name = cut_str;
	command->argc = 0;
	command->args = NULL;
	command->heredoc_lst = NULL;
	command->last = NULL;
	// command->last->last_in = NULL;
	// command->last->last_out = NULL;
	// command->last->in_type = NULL;
	// command->last->out_type = NULL;
	// command->heredoc_lst->heredoc = NULL;
	return (command);
}
