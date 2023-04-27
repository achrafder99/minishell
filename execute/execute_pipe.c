/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/04/27 20:18:01 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	exec_pipe_commande(t_command *cmd, t_info *info, t_env *env)
{
	char	**argv;
	char	**new_env;
	int		fid;
	int		flags;
	int		built_in;
	argv = get_argv(cmd, cmd->argc);
	flags = 0;
	built_in = 0;
	first_step(cmd, info, &built_in, &flags, env);
	if (built_in || flags == 127)
		return ;
	new_env = get_new_env(env->env);
	run_child(cmd, flags, built_in, argv,new_env);
}
void	execute_pipe(t_piped *piping, t_info *info, t_env *env)
{
	int	i, j;
	int	fd[piping->number_of_commands - 1][2];
	int	id;
	int tmpin;
	int tmpout;
	tmpin = dup(0);
	tmpout = dup(1);
	j = 0;
	while (j < (piping->number_of_commands - 1))
	{
		pipe(fd[j]);
		// printf("%d %d\n", fd[j][0], fd[j][1]);
		j++;
	}
	i = 0;
	while (i < piping->number_of_commands)
	{
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				// printf("rrr\n");
				close(fd[i][0]);
				dup2(fd[i][1], 1);
				exec_pipe_commande(&piping->command[i], info, env);
				close(fd[i][1]);
				close(1);
			}
			else if (i == piping->number_of_commands - 1 )
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
				exec_pipe_commande(&piping->command[i], info, env);
				close(fd[i - 1][0]);
				close(0);
			}
			else
			{
				close(fd[i - 1][1]);
				close(fd[i][0]);
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				close(fd[i][1]);
				close(fd[i - 1][0]);
				exec_pipe_commande(&piping->command[i], info, env);
			}
			
			// exit(0);
		}
		close (fd[i][1]);
		// close (fd[i][0]);
		wait(NULL);
			i++;
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		
	}
}

	// int	i;
	// int	j;

	// i = 0;
	// while (i < piping->number_of_commands)
	// {
	// 	printf("Command (%d)\n", i);
	// 	printf("command name :%s\n", piping->command[i].name);
	// 	printf("Args ");
	// 	j = 0;
	// 	while (j < piping->command[i].argc)
	// 	{
	// 		printf("%s\t", piping->command[i].args[j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	printf("in %s\n", piping->command[i].infile);
	// 	printf("out %s\n", piping->command[i].outfile);
	// 	printf("append %s\n", piping->command[i].append_mode);
	// 	printf("heredoc %s\n", piping->command[i].heredoc);
	// 	printf("end heredoc %s\n", piping->command[i].end_heredoc);
	// 	i++;
	// }