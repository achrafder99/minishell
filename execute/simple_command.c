/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 02:48:27 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char	**environ;

void	first_step(t_command *command, t_info *info, int *built_in, int *flags, t_lst *env)
{
	t_lst	*env;
	t_lst	*exp;
	env = get_env(env);
	exp = get_export_env(env);
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
		info->status_code = execute_built_in(command, info, env);
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

void	run_child(t_command *command, int flags, int built_in, char **argv, t_lst *env)
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
int	get_list_size(t_lst *lst)
{
	int	i;
	t_node	*tmp;

	i = 0;
	tmp = lst->top;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
char	**get_new_env(t_lst *env)
{
	char	**new;
	t_node	*tmp;
	int	size;
	
	size = get_list_size(env);
	tmp = env->top;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while
		
}

void	simple_command(t_command *command, t_info *info, t_env *env)
{
	char	**argv;
	char	**new_env;
	int		fid;
	int		flags;
	int		built_in;
	
	argv = get_argv(command, command->argc);
	flags = 0;
	built_in = 0;
	first_step(command, info, &built_in, &flags, env);
	if (built_in || flags == 127)
		return ;
	new_env = get_new_env(env->env)
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
