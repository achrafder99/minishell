/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/05/18 14:28:55 by aalami           ###   ########.fr       */
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
	env->env_arr = get_new_env(env->env);
	run_child(cmd, flags, built_in, argv,env);
}

void	execute_pipe(t_piped *piping, t_info *info, t_env *env)
{
	int	i, j;
	int	**fd;
	int outfile;
	int infile;
	int flag;

	fd = (int **)malloc(sizeof(int *) * piping->number_of_commands);
	if (!fd)
	{
		perror("");
		exit(1);
	}
	j = 0;
	while (j < piping->number_of_commands - 1)
	{
		fd[j] = malloc(sizeof (int) * 2);
		j++;
	}
	fd[j] = NULL;
	int	id[piping->number_of_commands];
	j = 0;
	while (j < (piping->number_of_commands - 1))
	{
		pipe(fd[j]);
		j++;
	}
	i = 0;
	while (i < piping->number_of_commands)
	{
		flag = 0;
		if (ft_strlen(piping->command[i].name))
		{
			if (!ft_strcmp(piping->command[i].name, "<<"))
			{
				flag = 1;
				info->status_code = 0;
			}
			if (piping->command[i].heredoc_lst)
				piping->command[i].data_lst = open_heredoc(piping->command[i].heredoc_lst);
			id[i] = fork();
			if (id[i] == 0)
			{
				if (!flag && !check_command(piping->command[i].name, env))
				{
					printf("minishell: %s: No such file or directory\n", piping->command[i].name);
					info->status_code= 127;
					exit (127);
				}
				
				if (i > 0)
					dup2(fd[i - 1][0], 0);
				if (fd[i] != NULL && !flag)
					dup2(fd[i][1], 1);
				// if (piping->command[i].outfile)
				// {
				// 	int outfile;
				// 	outfile = open(piping->command[i].outfile, O_RDWR,777);
				// 	dup2(outfile, fd[i - 1][1]);
				// }
				// printf("child %d: stdin=%d, stdout=%d\n", i, dup(0), dup(1));
				j = 0;
				while (j < (piping->number_of_commands - 1))
				{
					close(fd[j][0]);
					close(fd[j][1]);
					j++;
				}
				if (!flag)
					exec_pipe_commande(&piping->command[i], info, env);
				if (flag || check_is_built_in(piping->command[i].name))
					exit(info->status_code);
			}
			if ((check_is_built_in(piping->command[i].name) || i + 1 == piping->number_of_commands))
			{	if (!check_is_built_in(piping->command[i].name))
				{
					j = 0;
					while (j < (piping->number_of_commands - 1))
					{
						close(fd[j][0]);
						close(fd[j][1]);
						j++;
					}
				}
						waitpid(id[i], &info->status_code,0);
						if (WIFSIGNALED(info->status_code))
							info->status_code = WTERMSIG(info->status_code) + 128;
						else
							info->status_code = WEXITSTATUS(info->status_code);
			}
		}
		i++;
	}
	j = 0;
	while (j < (piping->number_of_commands - 1))
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	while(waitpid(-1, NULL, 0) > 0)
	;
	unlink(".heredoc");
	i = 0;
	while (i < piping->number_of_commands)
	{
		free(fd[i]);
		i++;
	}
	// free(fd[i]);
	free(fd);
	
	// {
	// 	if (WIFEXITED(info->status_code))
	// 	  info->status_code =  WEXITSTATUS(info->status_code);

	// }
	// {
	// 	printf("after%d\n", info->status_code);
	// }
	// 	;
	// {
	// 	if (info->status_code != 0 || info->status_code != 127 )
	// 		info->status_code =1;
	// }
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < piping->number_of_commands)
// 	{
// 		printf("Command (%d)\n", i);
// 		printf("command name :%s\n", piping->command[i].name);
// 		if (piping->command[i].argc)
// 		{			printf("Args ");
// 			j = 0;
// 			while (j < piping->command[i].argc)
// 			{
// 				printf("%s\t", piping->command[i].args[j]);
// 				j++;
// 			}}
// 		printf("\n");
// 		if (piping->command[i].heredoc_lst)
// 		{t_heredoc *tmp;
// 		tmp = piping->command[i].heredoc_lst->top;
// 		while(tmp)
// 		{
// 			printf("heredoc delimiter %s\n", tmp->delimit);
// 			tmp = tmp->next;
// 		}}
// 		// printf("last %s\n", piping->command[i].last->in_type);
// 		if (piping->command[i].last)
// {	printf("last in %s\n", piping->command[i].last->last_in);
// 	printf("last out %s\n", piping->command[i].last->last_out);
// 	}
// 		i++;
// 	}
}
