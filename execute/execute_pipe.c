/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/05/03 18:15:25 by aalami           ###   ########.fr       */
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
		exit(1);
	env->env_arr = get_new_env(env->env);
	run_child(cmd, flags, built_in, argv,env);

}
void	execute_pipe(t_piped *piping, t_info *info, t_env *env)
{
	// int	i, j;
	// int	**fd;
	// int outfile;
	// int infile;
	// fd = (int **)malloc(sizeof(int *) * piping->number_of_commands);
	// j = 0;
	// while (j < piping->number_of_commands - 1)
	// {
	// 	fd[j] = malloc(sizeof (int) * 2);
	// 	j++;
	// }
	// fd[j] = NULL;
	// int	id;
	// j = 0;
	// while (j < (piping->number_of_commands - 1))
	// {
	// 	pipe(fd[j]);
	// 	j++;
	// }
	// i = 0;
	// while (i < piping->number_of_commands)
	// {
	// 	id = fork();
	// 	if (id == 0)
	// 	{
	// 		if (!check_command(piping->command[i].name, env))
	// 		{
	// 			printf("minishell: %s: No such file or directory\n", piping->command[i].name);
	// 			info->status_code = 127;
	// 			exit(1) ;
	// 		}
	// 		if (i > 0)
	// 			dup2(fd[i - 1][0], 0);
	// 		if (fd[i] != NULL)
	// 			dup2(fd[i][1], 1);
	// 		// if (piping->command[i].outfile)
	// 		// {
	// 		// 	int outfile;
	// 		// 	outfile = open(piping->command[i].outfile, O_RDWR,777);
	// 		// 	dup2(outfile, fd[i - 1][1]);
	// 		// }
	// 		// printf("child %d: stdin=%d, stdout=%d\n", i, dup(0), dup(1));
	// 		j = 0;
	// 		while (j < (piping->number_of_commands - 1))
	// 		{
	// 			close(fd[j][0]);
	// 			close(fd[j][1]);
	// 			j++;
	// 		}
	// 		exec_pipe_commande(&piping->command[i], info, env);
	// 		if (check_is_built_in(piping->command[i].name))
	// 			exit(0);
	// 	}
	// 	i++;
	// }
	// j = 0;
	// while (j < (piping->number_of_commands - 1))
	// {
	// 	close(fd[j][0]);
	// 	close(fd[j][1]);
	// 	j++;
	// }
	// while(waitpid(-1, NULL, 0) > 0)
	// 	;
	int	i;
	int	j;

	i = 0;
	while (i < piping->number_of_commands)
	{
		printf("Command (%d)\n", i);
		printf("command name :%s\n", piping->command[i].name);
		printf("Args ");
		j = 0;
		while (j < piping->command[i].argc)
		{
			printf("%s\t", piping->command[i].args[j]);
			j++;
		}
		printf("\n");
		printf("in %s\n", piping->command[i].infile);
		printf("out %s\n", piping->command[i].outfile);
		printf("append %s\n", piping->command[i].append_mode);
		printf("heredoc %s\n", piping->command[i].heredoc);
		printf("end heredoc %s\n", piping->command[i].end_heredoc);
		printf("last %s\n", piping->command[i].last->type);
		printf("last %s\n", piping->command[i].last->last_file);
		i++;
	}
}
