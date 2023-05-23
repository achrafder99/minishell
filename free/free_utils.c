/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:39:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 21:04:59 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_components(t_components *head)
{
	t_components	*current;
	t_components	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current->type.type);
		free(current);
		current = next;
	}
}

void	free_heredoc(t_here_lst *lst_heredoc)
{
	t_heredoc	*list;

	if (lst_heredoc == NULL)
		return ;
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
	if (command == NULL)
		return ;
	if (command->heredoc_lst)
	{
		free_heredoc(command->heredoc_lst);
		free_data(command->data_lst);
	}
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
	if (command->args != NULL)
		free_things(command->args);
	free(command);
	command = NULL;
}

void	free_all_data(t_piped *pipe_line, int i)
{
	if (pipe_line->command[i].heredoc_lst)
	{
		free_heredoc(pipe_line->command[i].heredoc_lst);
		free_data(pipe_line->command[i].data_lst);
	}
	if (pipe_line->command[i].last_in && pipe_line->command[i].in_type)
	{
		free(pipe_line->command[i].last_in);
		free(pipe_line->command[i].in_type);
	}
	if (pipe_line->command[i].last_out
		&& pipe_line->command[i].out_type)
	{
		free(pipe_line->command[i].last_out);
		free(pipe_line->command[i].out_type);
	}
}

void	free_pipe_line(t_piped *pipe_line)
{
	int	i;

	i = 0;
	if (pipe_line)
	{
		while (i < pipe_line->number_of_commands)
		{
			free_things(pipe_line->command[i].args);
			free_all_data(pipe_line, i);
			i++;
		}
		return (free(pipe_line->command), free(pipe_line));
	}
}
