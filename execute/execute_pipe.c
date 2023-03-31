/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:47:55 by adardour          #+#    #+#             */
/*   Updated: 2023/03/31 05:01:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_pipe(t_piped *pipe) {
    printf("Number of commands: %d\n", pipe->number_of_commands);
    int i = 0;
    while (i < pipe->number_of_commands) {
        printf("=======  Command (%d)\n",i + 1);
        printf("Command (%d): %s\n", i, pipe->command[i].name);
        printf("Arg ");
        int j = 0;
        while (j < pipe->command[i].argc)
        {
            printf("%s ",pipe->command[i].args[j]);
            j++;
        }
        printf("\n");
        printf("infile (%d): %s\n", i, pipe->command[i].infile);
        printf("append_mode (%d): %s\n", i, pipe->command[i].append_mode);
        printf("outfile (%d): %s\n", i, pipe->command[i].outfile);
        printf("======== \n");
        i++;
    }

    int j = 0;
     i = 0;
    while (j < pipe->command[i].argc)
    {
        free(pipe->command[i].args[j]);
        j++;
        i++;
    }
    free(pipe->command[i].args);
    free(pipe->command[i].infile);
    free(pipe->command[i].outfile);
    free(pipe->command[i].append_mode);
    i = 0; 
    while (i < pipe->number_of_commands)
    {
        free(pipe->command[i].name);
        i++;
    }
    free(pipe->command);
    free(pipe);
}