/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:03:03 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 23:20:12 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_command_not_found(t_info *info, t_command *command, int *flags)
{
	printf("minishell: %s: No such file or directory\n", command->name);
	info->status_code = 127;
	*flags = 127;
}

void	first_step(t_command *command, t_info *info, int *flags, t_env *env)
{
	int	save_in;
	int	save_out;
    int redirect;

    redirect = 0;
	if (!check_command(command->name, env))
		return (handle_command_not_found(info, command, flags));
	save_in = -1;
	save_out = -1;
	if (check_type(command->in_type) || check_type(command->out_type))
		*flags = 1;
	if (check_is_built_in(command->name))
	{		
		if (*flags)
			redirect = save_and_redirect(command, &save_in, &save_out);
        if (redirect != -1)
		    execute_built_in(command, info, env);
		if (save_in != -1 || save_out != -1)
            reset_std_in_out(command, save_in, save_out);
		if (command->data_lst)
			unlink(".heredoc");
	}
    if (redirect == -1)
	    info->status_code = 1;
}

void	run_child(t_command *command, int flags, char **argv, t_env *env)
{
	t_fds	*fds;
	char	*cmd;
    int redirect;

	redirect = redirection(command, command->data_lst);
	cmd = get_cmd(command->name);
    if (redirect != -1)
		execve(cmd, argv, env->env_arr);
	else
		exit (1);
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
