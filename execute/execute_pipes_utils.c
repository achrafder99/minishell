/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:11 by aalami            #+#    #+#             */
/*   Updated: 2023/06/07 13:19:55 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**creat_pipes(t_piped *piping)
{
	int	j;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * piping->number_of_commands);
	if (!fd)
	{
		perror("");
		exit(1);
	}
	j = 0;
	while (j < piping->number_of_commands - 1)
	{
		fd[j] = malloc(sizeof(int) * 2);
		if (!fd[j])
		{
			perror("error occcured");
			exit(1);
		}
		j++;
	}
	fd[j] = NULL;
	return (fd);
}

void	open_pipes(t_piped *piping, int **fd)
{
	int	j;

	j = 0;
	while (j < (piping->number_of_commands - 1))
	{
		pipe(fd[j]);
		j++;
	}
}

void	close_pipes(int **fd)
{
	int	j;

	j = 0;
	while (fd[j] != NULL)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	check_command_not_found(int flag, t_info *info, t_env *env,
		char *cmd_name)
{
	if (!flag && !check_command(cmd_name, env, info))
	{
		write(2, "tsh: ", 6);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": ", 3);
		write(2, "command not found\n", 19);
		info->status_code = 127;
		exit(127);
	}
}

void	duplicate_read_write(int i, int **fd, int flag)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	if (i > 0)
		in = dup2(fd[i - 1][0], 0);
	if (fd[i] != NULL && !flag)
		out = dup2(fd[i][1], 1);
	if (in == -1 || out == -1)
	{
		perror("error occured");
		exit(1);
	}
	close_pipes(fd);
}
