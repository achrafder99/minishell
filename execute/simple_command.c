/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 20:41:36 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char **environ;

char *to_lower(char *input){
    int i;
    i = 0;

    char *str;
    str = malloc(ft_strlen(input) + 1);
    if(!str){
        return (NULL);
        exit(1);
    }
    while (input[i] != '\0')
    {
        if(input[i] >= 65 && input[i] <= 90)
            str[i] = input[i] + 32;
        else
            str[i] = input[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void simple_command(t_command *command)
{
    t_fds fds;
    // printf("Command name :%s\n",command->name);
    // printf("outfile name :%s\n",command->outfile);
    // printf("infile name :%s\n",command->infile);
    // return;
    int i;
    i = 0;
    int flags;
    int redirect_out;
    int redirect_in;
    int append;
    redirect_out = 0;
    redirect_in = 0;
    append = 0;
    flags = 0;
    
    int fd;
    char *str;

    int fd1;
    str = to_lower(command->name);
    if(!check_command(command->name))
    {
        printf("tsh: ");
        printf("%s: ",command->name);
        printf("command not found\n");
        return;
    }
    if(check_is_built_in(command->name))
        flags = 1;
    if(is_redirect(command))
    {
        if(command->outfile)
        {
            fds.fd_out = open(command->outfile,O_WRONLY | O_CREAT | O_TRUNC,0777);
            redirect_out = 1;
        }
        if(command->infile){
            fds.fd_in = open(command->infile,O_RDONLY,0777);
            redirect_in = 1;
        }
        if(command->append_mode)
        {
            fds.fd_append = open(command->append_mode,O_WRONLY | O_CREAT | O_APPEND,0777);
            append = 1;
        }
    }
    
    pid_t fid;
    char *cmd;
    char **argv;
    i = 0;
    char **spliting;
    int exec;
    exec = 0;
    spliting = ft_split(getenv("PATH"),':');
    i = 0;
    char *join;
    while (spliting[i] != NULL && !flags)
    {
        cmd = ft_strjoin(spliting[i],"/");
        join = ft_strjoin(cmd,command->name);
        if(!access(join,X_OK)){
            cmd = join;
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
    if(fid == 0)
    {
        if(redirect_in){
            if(dup2(fds.fd_in,STDIN_FILENO) == -1)
            {
                perror("error occurred.");
                exit(1);
            }
            close(fds.fd_in);
        }
        if (redirect_out || append)
        { 
            if(redirect_out)
            {
                if(dup2(fds.fd_out,STDOUT_FILENO) == -1)
                {
                    perror("error occurred.");
                    exit(1);
                }
                close(fds.fd_out);
            }
            else{
                if(dup2(fds.fd_append,STDOUT_FILENO) == -1)
                {
                    perror("error occurred.");
                    exit(1);
                }
                close(fds.fd_append);
            }
        }
        if (flags)
        {
            command->name = str;
            execute_built_in(command);
            exit(0);
        }
        else
        {
            argv = get_argv(command,command->argc);
            if(exec)
                execve(cmd,argv,environ);
            else{
                execve(command->name,argv,environ);
            }
        }
    }
    else
        wait(NULL);
}