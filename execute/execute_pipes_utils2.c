/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:14:31 by aalami            #+#    #+#             */
/*   Updated: 2023/06/05 13:07:44 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_heredoc(t_command *command, t_info *info)
{
	if (check_is_redirection(command->name))
	{
		info->flags = 1;
		info->status_code = 0;
	}
	if (command->heredoc_lst)
		command->data_lst = open_heredoc(command->heredoc_lst, info);
}

void	complete_pipes_ex(int flag, t_command *command, t_info *info,
		t_env *env)
{
	if (!flag)
		exec_pipe_commande(command, info, env);
	if (flag || check_is_built_in(command->name) || info->status_code == 126)
		exit(info->status_code);
}

void	wait_for_last_exit(int id, int **fd, t_info *info,
		t_command *command)
{
	(void)command;
	close_pipes(fd);
	wait_for_exit_state(id, info);
}

int	*allocate_for_ids(t_piped *piping)
{
	int	*id;

	id = malloc(sizeof(int) * piping->number_of_commands);
	if (!id)
	{
		perror("");
		exit(1);
	}
	return (id);
}

int	fork_id(int *id, int i, t_info *info)
{
	id[i] = fork();
	if (id[i] == -1)
	{
		perror("");
		info->status_code = 1;
		return (1);
	}
	return (0);
}
