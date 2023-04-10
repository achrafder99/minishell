/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:41:37 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 05:13:38 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*init_command(t_command *command, char *cut_str)
{
	command = (t_command *) malloc(sizeof(t_command));
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
	command->last = NULL;
	return (command);
}
