/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:47:21 by adardour          #+#    #+#             */
/*   Updated: 2023/03/28 02:22:12 by adardour         ###   ########.fr       */
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
// printf("Heredoc  :%s\n",command->heredoc);
// return;

void display_heredoc(int fd){
    
    char *line;
    line = get_next_line(fd);
    while (line != NULL)
    {
        write(1,line,ft_strlen(line));
        line = get_next_line(fd);
    }
}

void simple_command(t_command *command) {
    int flags;
    flags = 0;
    int fd;
    if(check_is_built_in(command->name)){
        execute_built_in(command);
        flags = 1;
    }
    if (command->heredoc) {
        int fd;
        fd = fork();
        int fdd;
        if(fd == 0){
            char *line;
            write(1,"heredoc> ",9);
            line = get_next_line(0);
            line[ft_strlen(line) - 1] = '\0'; 
            fdd = open("/tmp/heredoc",O_RDWR | O_CREAT | O_APPEND,0777);
            write(fdd,ft_strjoin(line,"\n"),ft_strlen(line) + 1);
            while (1) {
                fdd = open("/tmp/heredoc",O_RDWR | O_CREAT | O_APPEND,0777);
                write(1,"heredoc> ",9);
                line = get_next_line(0);
                line[ft_strlen(line) - 1] = '\0'; 
                if(!ft_strcmp(line,command->heredoc))
                    break;
                write(fdd,ft_strjoin(line,"\n"),ft_strlen(line) + 1);
                close(fdd);
            }
            unlink("/tmp/heredoc");
            display_heredoc(fdd);
            close(fdd);
        }
        else
            wait(NULL);
    }
    return;
    if(is_redirect(command)){
        if(command->outfile)
            fd = open(command->outfile,O_WRONLY | O_CREAT | O_TRUNC,0777);
        else if(command->append_mode)
            fd = open(command->append_mode,O_WRONLY | O_CREAT | O_APPEND,0777);
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
    int exec;
    exec = 0;
    spliting = ft_split(getenv("PATH"),':');
    i = 0;
    while (spliting[i] != NULL)
    {
        cmd = ft_strjoin(spliting[i],"/");
        if(access(ft_strjoin(cmd,command->name),X_OK) == 0){
            cmd = ft_strjoin(cmd,command->name);
            exec = 1;
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
        if(exec)
            execve(cmd,argv,NULL);
        else
            execve(command->name,argv,NULL);
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