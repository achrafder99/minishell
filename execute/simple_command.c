/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/05/11 14:50:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char	**environ;

void	handle_fds(t_fds *fds, t_command *command)
{
	fds = malloc(sizeof(t_fds));
	fds->fd_out = open(command->outfile, O_RDWR, 0777);
	fds->fd_in = open(command->infile, O_RDWR, 0777);
	fds->fd_append = open(command->append_mode, O_RDWR | O_APPEND, 0777);
}

void	first_step(t_command *command, t_info *info, int *built_in, int *flags, t_env *env)
{
	int		save;
	t_fds	*fds;
	if (!check_command(command->name, env))
	{
		printf("minishell: %s: No such file or directory\n", command->name);
		info->status_code = 127;
		*flags = 127;
		return ;
	}
	save = -1;
	if (command->last != NULL)
	{
		if (check_type(command->last->type))
			*flags = 1;
	}
	if (check_is_built_in(command->name))
	{
		if (*flags)
		{
			handle_fds(fds, command);
			if (!ft_strcmp(command->last->type, "REDIRECT_in"))
				save = dup(STDIN_FILENO);
			else
				save = dup(STDOUT_FILENO);
			redirection(command, command->last->type, \
			command->last->last_file, fds);
		}
		execute_built_in(command, info, env);
		if (save != -1)
		{
			if (!ft_strcmp(command->last->type, "REDIRECT_in"))
				dup2(save, STDIN_FILENO);
			else
				dup2(save, STDOUT_FILENO);
		}
		*built_in = 1;
	}
}


void	run_child(t_command *command, int flags, \
int built_in, char **argv, t_env *env)
{
	t_fds	*fds;
	char	*cmd;
	if (flags)
	{
		handle_fds(fds, command);
		redirection(command, command->last->type, \
		command->last->last_file, fds);
	}
	cmd = get_cmd(command->name);
	execve(cmd, argv, env->env_arr);
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
	char	*key;
	t_node	*tmp;
	int	size;
	int	i;
	
	size = get_list_size(env);
	tmp = env->top;
	i = 0;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while(tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			new[i] = ft_strjoin(key, tmp->value);
		else
			new[i] = ft_strdup(key);
		free(key);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	simple_command(t_command *command, t_info *info, t_env *env)
{	
	char	**argv;
	int		fid;
	int		flags;
	int		built_in;
	char 	**spliting;

	argv = get_argv(command, command->argc);
	flags = 0;
	built_in = 0;
	first_step(command, info, &built_in, &flags, env);
	if (built_in || flags == 127)
		return ;
	env->env_arr = get_new_env(env->env);
	if (command)
	fid = fork();
	if (fid == 0)
		run_child(command, flags, built_in, argv,env);
	else
	{
		waitpid(fid, &info->status_code,0);
		if (WIFSIGNALED(info->status_code))
			info->status_code = WTERMSIG(info->status_code) + 128;
		else
			info->status_code = WEXITSTATUS(info->status_code);
		// if (info->status_code != 0)
		// 	info->status_code = 1;
	}
}
