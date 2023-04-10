/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 00:09:30 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char	**environ;

void	first_step(t_command *command, t_info *info, int *built_in, int *flags)
{
	if (!check_command(command->name))
	{
		printf("command not found :\n");
		info->status_code = 127;
		return ;
	}
	if (command->last != NULL)
	{
		if (check_type(command->last->type))
			*flags = 1;
	}
	if (check_is_built_in(command->name))
	{
		info->status_code = execute_built_in(command, info);
		*built_in = 1;
	}
}

void	handle_fds(t_fds *fds, t_command *command)
{
	fds = malloc(sizeof(t_fds));
	fds->fd_out = open(command->outfile, O_RDWR, 0777);
	fds->fd_in = open(command->infile, O_RDWR, 0777);
	fds->fd_append = open(command->append_mode, O_RDWR | O_APPEND, 0777);
}

void	run_child(t_command *command, int flags, int built_in, char **argv,char **env)
{
	t_fds	*fds;
	char	*cmd;

	if (!check_command(command->name))
		return (perror("not found "), exit(127));
	if (flags)
	{
		handle_fds(fds, command);
		redirection(command->last->type, command->last->last_file, fds);
	}
	cmd = get_cmd(command->name);
	if (!built_in)
		execve(cmd, argv, NULL);
	exit(1);
}

void	simple_command(t_command *command, t_info *info, char **env)
{
	char	**argv;
	int		fid;
	int		flags;
	int		built_in;

	argv = get_argv(command, command->argc);
	flags = 0;
	built_in = 0;
	first_step(command, info, &built_in, &flags);

	fid = fork();
	if (fid == 0)
		run_child(command, flags, built_in, argv,env);
	else
	{
		waitpid(fid, &info->status_code, 0);
		if (info->status_code != 0)
			info->status_code = 1;
	}
}
