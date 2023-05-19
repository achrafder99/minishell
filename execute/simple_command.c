/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:12:11 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 23:04:26 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	save_and_redirect(t_command *command, int *save_in, int *save_out)
{
	if (command->last_in)
		*save_in = dup(STDIN_FILENO);
	if (command->last_out)
		*save_out = dup(STDOUT_FILENO);
	return (redirection(command, command->data_lst));
}

void    reset_std_in_out(t_command *command , int save_in, int save_out)
{
    if (command->last_in)
		dup2(save_in, STDIN_FILENO);
	if (command->last_out)
		dup2(save_out, STDOUT_FILENO);
}

void	wait_for_child(t_info *info, int fid, char **argv, t_env *env)
{
	waitpid(fid, &info->status_code, 0);
	if (WIFSIGNALED(info->status_code))
		info->status_code = WTERMSIG(info->status_code) + 128;
	else
		info->status_code = WEXITSTATUS(info->status_code);
	free_execution_args(argv, env);
}

void	simple_command(t_command *command, t_info *info, t_env *env)
{
	char	**argv;
	int		fid;
	int		flags;
	char	**spliting;

	argv = get_argv(command, command->argc);
	flags = 0;
	if (command->heredoc_lst)
		command->data_lst = open_heredoc(command->heredoc_lst);
	first_step(command, info, &flags, env);
	if (check_is_built_in(command->name) || flags == 127)
		return (free_execution_args(argv, env));
	env->env_arr = get_new_env(env->env);
	if (command)
		fid = fork();
	if (fid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		run_child(command, flags, argv, env);
	}
	else
		wait_for_child(info, fid, argv, env);
	unlink(".heredoc");
}
