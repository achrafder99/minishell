/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:12:11 by aalami            #+#    #+#             */
/*   Updated: 2023/06/02 18:30:28 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	save_and_redirect(t_command *command, int *save_in, int *save_out,
		t_info *info)
{
	if (command->last_in)
		*save_in = dup(STDIN_FILENO);
	if (command->last_out)
		*save_out = dup(STDOUT_FILENO);
	return (redirection(command, command->data_lst, info));
}

void	reset_std_in_out(t_command *command, int save_in, int save_out,
		t_info *info)
{
	if (command->last_in)
		if (dup2(save_in, STDIN_FILENO) == -1)
			perror("dup");
	if (command->last_out)
		if (dup2(save_out, STDOUT_FILENO) == -1)
			perror("dup");
	if (info->fd_in != -1 && info->fd_in != -2)
		close(info->fd_in);
	if (info->fd_out != -1 && info->fd_in != -2)
		close(info->fd_out);
	close(save_in);
	close(save_out);
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
	{
		info->env = env;
		command->data_lst = open_heredoc(command->heredoc_lst, info);
	}
	if (check_empty_command(command->name, info, &flags) \
		|| g_heredoc_flag == -1)
		return (free_execution_args(argv, env));
	first_step(command, info, &flags, env);
	if (check_is_built_in(command->name) || flags == 127 || flags == 126)
		return (free_execution_args(argv, env));
	if (env->env->top)
		env->env_arr = get_new_env(env->env);
	fid = fork();
	if (fid == 0)
		run_child(command, argv, env, info);
	else
		wait_for_child(info, fid, argv, env);
}
