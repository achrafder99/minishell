/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:40:04 by adardour          #+#    #+#             */
/*   Updated: 2023/05/17 18:48:12 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_heredoc(t_here_lst *lst_heredoc)
{
	t_heredoc *list;
	list = lst_heredoc->top;
	while (list)
	{
		free(list->delimit);
		free(list->heredoc);
		free(list);
		list = list->next;
	}
	free(list);
	free(lst_heredoc);
}

void	free_command(t_command *command)
{
	if(command->heredoc_lst)
		free_heredoc(command->heredoc_lst);
	free(command);
}

void	piped(t_piped *pipe_line, t_command *command, t_info *info,t_env *env)
{
	t_command	*new_commands;

	if (!pipe_line)
	{
		simple_command(command, info,env);
		if (command->last_in && command->in_type)
		{
			free(command->last_in);
			free(command->in_type);
		}
		if (command->last_out && command->out_type)
		{
			free(command->last_out);
			free(command->out_type);
		}
		if (command)
			free_command(command);
		return;
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
		execute_pipe(pipe_line, info, env);
		return;
	}
}
