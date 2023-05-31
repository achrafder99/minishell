/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:03:03 by aalami            #+#    #+#             */
/*   Updated: 2023/05/31 00:49:52 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_command_not_found(t_info *info, t_command *command, int *flags)
{
	if (info->status_code == 126)
	{
		write(2, "tsh: ", 6);
		write(2, command->name, ft_strlen(command->name));
		write(2, ": ", 3);
		write(2, "is a directory\n", 16);
	}
	else
	{
		write(2, "tsh: ", 6);
		write(2, command->name, ft_strlen(command->name));
		write(2, ": ", 3);
		write(2, "command not found\n", 19);
		info->status_code = 127;
		*flags = 127;
	}
}

int	check_empty_command(char *command, t_info *info, int *flag)
{
	if (ft_strlen(command) == 0)
	{
		info->status_code = 0;
		*flag = 2;
		return (1);
	}
	return (0);
}

void	first_step(t_command *command, t_info *info, int *flags, t_env *env)
{
	int	save_in;
	int	save_out;
	int	redirect;

	redirect = 0;
	if (!check_command(command->name, env, info) || check_command(command->name,
			env, info) == 126)
		return (handle_command_not_found(info, command, flags));
	save_in = -1;
	save_out = -1;
	if (check_type(command->in_type) || check_type(command->out_type))
		*flags = 1;
	if (check_is_built_in(command->name))
	{
		if (*flags)
			redirect = save_and_redirect(command, &save_in, &save_out, info);
		if (redirect != -1)
			execute_built_in(command, info, env);
		if (save_in != -1 || save_out != -1)
			reset_std_in_out(command, save_in, save_out, info);
		if (command->data_lst && unlink(".heredoc") == -1)
			perror("unlink");
	}
	if (redirect == -1)
		info->status_code = 1;
}

void	run_child(t_command *command, char **argv, t_env *env, t_info *info)
{
	char	*cmd;
	int		redirect;

	redirect = redirection(command, command->data_lst, info);
	cmd = get_cmd(command->name, env, info);
	if (redirect != -1)
		execve(cmd, argv, env->env_arr);
	else
		exit(1);
}

void	free_execution_args(char **argv, t_env *env)
{
	if (argv)
	{
		free_things(argv);
		argv = NULL;
	}
	if (env->env_arr)
	{
		free_things(env->env_arr);
		env->env_arr = NULL;
	}
}
