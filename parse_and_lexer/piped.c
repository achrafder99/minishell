/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:40:04 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 01:40:15 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	piped(t_piped *pipe_line, t_command *command, t_info *info, char **env)
{
	t_command	*new_commands;

	if (!pipe_line)
	{
		simple_command(command, info, env);
		if (command->argc > 0)
			free_things(command->args);
		return ;
	}
	else
	{
		pipe_line->number_of_commands++;
		new_commands = (t_command *) \
		malloc(pipe_line->number_of_commands * sizeof(t_command));
		if (pipe_line->command)
		{
			ft_memcpy(new_commands, pipe_line->command, \
			(pipe_line->number_of_commands -1) * sizeof(t_command));
			free(pipe_line->command);
		}
		new_commands[pipe_line->number_of_commands - 1] = *command;
		pipe_line->command = new_commands;
		execute_pipe(pipe_line);
		return ;
	}
}
