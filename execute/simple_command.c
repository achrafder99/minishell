/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:47:21 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 22:00:32 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

    // printf("Command name :%s\n",command->name);
    // printf("Args :");
    // printf("%s ",command->args[0]);
    // // printf("%s ",command->args[1]);
    // printf("\n");
    // printf("infile  :%s\n",command->infile);
    // printf("outfile  :%s\n",command->outfile);
    // printf("argc  :%d\n",command->argc);
    // printf("append_mode  :%s\n",command->append_mode);

void simple_command(t_command *command) {
    int flags;
    flags = 0;
    int fd;
    if(check_is_built_in(command->name)){
        execute_built_in(command);
        flags = 1;
    }
    if(is_redirect(command)){
        fd = open(command->outfile,O_WRONLY | O_CREAT | O_TRUNC,0777);
        if(fd == -1){
            perror("");
            exit(1);
        }
        if(dup2(fd,STDOUT_FILENO) == -1){
            perror("error occurred.");
            exit(1);
        }
        close(fd);
        if(flags)
            return;
    }
    pid_t fid;
    char *cmd;
    char **argv;
    int i = 0;
    char **spliting;
    spliting = ft_split(getenv("PATH"),':');
    i = 0;
    while (spliting[i] != NULL)
    {
        cmd = ft_strjoin(spliting[i],"/");
        if(access(ft_strjoin(cmd,command->name),X_OK) == 0){
            cmd = ft_strjoin(cmd,command->name);
            break;
        }
        i++;
    }
    fid = fork();
    if(fid == -1){
        printf("Error\n");
        return;
    }
    if(fid == 0){
        argv = get_argv(command,command->argc);
        execve(cmd,argv,NULL);
    }
    else
        wait(NULL);
    i = 0;
    while (spliting[i] != NULL)
    {
        free(spliting[i]);
        i++;
    }
	dup2(STDIN_FILENO, 1);
    free(spliting[i]);
    free(spliting);
    spliting = NULL;
    i = 0;
    while (i < command->argc)
    {
        free(command->args[i]);
        i++;
    }
    free(command->args);
    command->args = NULL;
}