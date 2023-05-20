/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:11 by aalami            #+#    #+#             */
/*   Updated: 2023/05/20 18:42:19 by aalami           ###   ########.fr       */
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
	if (!flag && !check_command(cmd_name, env))
	{
		printf("minishell: %s: No such file or directory\n", cmd_name);
		info->status_code = 127;
		exit(127);
	}
}

void	duplicate_read_write(int i, int **fd, int flag)
{
	int	in;
	int	out;

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
