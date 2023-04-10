/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 20:46:11 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_step(t_command *command, t_info *info, int *built_in, int *flags)
{
	if (!check_command(command->name))
	{
		printf("command not found :\n");
		info->status_code = 127;
		*flags = 127;
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

void	run_child(int flags, int built_in, t_simple_command t_command)
{
	t_fds	*fds;
	char	*cmd;

	if (!check_command(t_command.command->name))
		return (perror("not found "), exit(127));
	if (flags)
	{
		handle_fds(fds, t_command.command);
		redirection(t_command.command->last->type, \
		t_command.command->last->last_file, fds);
	}
	cmd = get_cmd(t_command.command->name);
	if (!built_in)
		execve(cmd, t_command.command->args, t_command.env);
	exit(1);
}

void	simple_command(t_command *command, t_info *info, char **env)
{
	t_simple_command	t_command;
	int					fid;
	int					flags;
	int					built_in;

	t_command.env = env;
	t_command.command = command;
	t_command.command->args = get_argv(command, command->argc);
	flags = 0;
	built_in = 0;
	first_step(command, info, &built_in, &flags);
	if (built_in || flags == 127)
		return ;
	fid = fork();
	if (fid == 0)
		run_child(flags, built_in, t_command);
	else
	{
		waitpid(fid, &info->status_code, 0);
		if (info->status_code != 0)
			info->status_code = 1;
	}
}
