/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:14:31 by aalami            #+#    #+#             */
/*   Updated: 2023/05/22 23:06:28 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_heredoc(t_command *command, t_info *info)
{
	if (!ft_strcmp(command->name, "<<"))
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
	if (flag || check_is_built_in(command->name))
		exit(info->status_code);
}

void	process_buit_in_pipes(int id, int **fd, t_info *info,
		t_command *command)
{
	if (!check_is_built_in(command->name))
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
