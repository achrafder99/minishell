/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:41:37 by adardour          #+#    #+#             */
/*   Updated: 2023/05/03 19:32:16 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_command(t_command *command, char *cut_str)
{
	command = (t_command *) malloc(sizeof(t_command));
	command->last = (t_last_file *) malloc(sizeof(t_last_file));
	if (!command)
	{
		return (NULL);
		exit(1);
	}
	command->name = cut_str;
	command->argc = 0;
	command->args = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->append_mode = NULL;
	command->heredoc = NULL;
	command->end_heredoc = NULL;
	command->last->last_file = NULL;
	command->last->type = NULL;
	// command->heredoc_lst = NULL;
	// command->heredoc_lst->heredoc = NULL;
	return (command);
}
