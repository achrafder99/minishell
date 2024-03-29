/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/06/04 22:46:40 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipe_commande(t_command *cmd, t_info *info, t_env *env)
{
	char	**argv;
	int		flags;
	int		built_in;

	argv = get_argv(cmd, cmd->argc);
	flags = 0;
	built_in = 0;
	first_step(cmd, info, &flags, env);
	if (check_is_built_in(cmd->name) || flags == 127)
		return ;
	env->env_arr = get_new_env(env->env);
	run_child(cmd, argv, env, info);
}

void	wait_for_exit_state(int id, t_info *info)
{
	waitpid(id, &info->status_code, 0);
	if (WIFSIGNALED(info->status_code))
		info->status_code = WTERMSIG(info->status_code) + 128;
	else
		info->status_code = WEXITSTATUS(info->status_code);
}

void	start_pipe_execution(t_piped *piping, t_info *info, t_env *env,
		int **fd)
{
	int	i;

	i = -1;
	info->env = env;
	info->id = allocate_for_ids(piping);
	while (++i < piping->number_of_commands)
	{
		info->flags = 0;
		if (!ft_strlen(piping->command[i].name))
			continue ;
		check_for_heredoc(&piping->command[i], info);
		if (g_heredoc_flag == -1 || fork_id(info->id, i, info))
			break ;
		else if (info->id[i] == 0)
		{
			check_command_not_found(info->flags, info, env,
				piping->command[i].name);
			duplicate_read_write(i, fd, info->flags);
			complete_pipes_ex(info->flags, &piping->command[i], info, env);
		}
		if (i + 1 == piping->number_of_commands)
			wait_for_last_exit(info->id[i], fd, info, &piping->command[i]);
	}
	free(info->id);
}

void	free_pipes(int **fd, t_piped *piping)
{
	int	i;

	i = 0;
	while (i < piping->number_of_commands - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd[i]);
	free(fd);
}

void	execute_pipe(t_piped *piping, t_info *info, t_env *env)
{
	int	**fd;

	fd = creat_pipes(piping);
	open_pipes(piping, fd);
	start_pipe_execution(piping, info, env, fd);
	close_pipes(fd);
	while (waitpid(-1, NULL, 0) > 0)
		;
	unlink(".heredoc");
	free_pipes(fd, piping);
}
