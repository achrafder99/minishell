/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:49:36 by adardour          #+#    #+#             */
/*   Updated: 2023/05/13 20:21:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_piped	*create_new_pipeline(t_command **command)
{
	t_piped	*pipeline;

	pipeline = malloc(sizeof(t_piped));
	if (!pipeline)
		exit(1);
	pipeline->number_of_commands = 1;
	pipeline->command = malloc(sizeof(t_command));
	if (!pipeline->command)
	{
		free(pipeline);
		exit(1);
	}
	pipeline->command[0] = **command;
	return (pipeline);
}

void	add_command_to_pipeline(t_piped **pipeline, t_command **command)
{
	t_command	*new_commands;

	(*pipeline)->number_of_commands++;
	new_commands = malloc((*pipeline)->number_of_commands * sizeof(t_command));
	if (!new_commands)
		exit(1);
	if ((*pipeline)->command)
	{
		ft_memcpy(new_commands, (*pipeline)->command,
				((*pipeline)->number_of_commands - 1) * sizeof(t_command));
		free((*pipeline)->command);
	}
	new_commands[(*pipeline)->number_of_commands - 1] = **command;
	(*pipeline)->command = new_commands;
}

void	handle_pipe(t_components *node,
					t_piped **pipe_line,
					t_command **command)
{
	if (!*pipe_line)
		*pipe_line = create_new_pipeline(command);
	else
		add_command_to_pipeline(pipe_line, command);
}
