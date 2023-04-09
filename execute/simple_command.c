/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:47:21 by adardour          #+#    #+#             */
/*   Updated: 2023/04/07 00:47:18 by aalami           ###   ########.fr       */
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

void simple_command(t_command *command, t_lst *env, t_lst *exp, int child) {

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
    if(check_is_built_in(command->name))
    {
        execute_built_in(command, env, exp);
        return ;
    }
        // flags = 1;
        
    if(is_redirect(command)){
        if(command->outfile){
            fd = open(command->outfile,O_WRONLY | O_CREAT | O_TRUNC,0777);
            redirect_out = 1;
        }
        else if(command->append_mode){
            fd = open(command->append_mode,O_WRONLY | O_CREAT | O_APPEND,0777);
            append = 1;
        }
        else if(command->infile){
            fd = open(command->infile,O_RDONLY,0777);
            redirect_in = 1;
        }
        if(fd == -1){
            perror("");
            exit(1);
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
            free(cmd);
            cmd = join;
            exec = 1;
            break;
        }
        i++;
    }
    // exp->flag = 1;
    fid = fork();
        child = 1;
    if(fid == -1){
        printf("Error\n");
        return;
    }
    if(fid == 0){
        
        if (redirect_out || append)
        { 
            if(dup2(fd,STDOUT_FILENO) == -1){
                perror("error occurred.");
                exit(1);
            }
            close(fd);
        }
        else if(redirect_in){
            if(dup2(fd,STDIN_FILENO) == -1){
                perror("error occurred.");
                exit(1);
            }
            close(fd);
        }
        if (flags)
        {
            command->name = str;
            execute_built_in(command, env, exp);
            exit(0);
            free(str);
        }
        else
        {
            argv = get_argv(command,command->argc);
            if(exec)
                execve(cmd,argv,environ);
            else
                execve(command->name,argv,environ);
        }
    }
    else
        wait(NULL);
        free(command);
}