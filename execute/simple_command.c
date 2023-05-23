/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:12:11 by aalami            #+#    #+#             */
/*   Updated: 2023/05/23 20:19:35 by adardour         ###   ########.fr       */
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

void	reset_std_in_out(t_command *command, int save_in, int save_out)
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

	argv = get_argv(command, command->argc);
	flags = 0;
	fid = 0;
	if (command->heredoc_lst)
		command->data_lst = open_heredoc(command->heredoc_lst, info);
	if (check_empty_command(command->name, info, &flags) \
	|| g_heredoc_flag == -1)
		return (free_execution_args(argv, env));
	first_step(command, info, &flags, env);
	if (check_is_built_in(command->name) || flags == 127)
		return (free_execution_args(argv, env));
	signal(SIGQUIT, SIG_DFL);
	if (env->env->top)
		env->env_arr = get_new_env(env->env);
	fid = fork();
	if (fid == 0)
		run_child(command, argv, env);
	else
		wait_for_child(info, fid, argv, env);
	unlink(".heredoc");
}
