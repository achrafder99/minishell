/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:51:55 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipe(t_piped *piping)
{
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
		i++;
	}
}
