/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:47:21 by adardour          #+#    #+#             */
/*   Updated: 2023/03/31 05:05:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char **environ;

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

// void display_heredoc(int fd){
    
//     char *line;
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         write(1,line,ft_strlen(line));
//         line = get_next_line(fd);
//     }
// }

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

// return;
// printf("Command name :%s\n",command->name);
// printf("Args :");
// printf("\n");
// printf("infile  :%s\n",command->infile);
// printf("outfile  :%s\n",command->outfile);
// printf("argc  :%d\n",command->argc);
// printf("append_mode  :%s\n",command->append_mode);
// printf("Heredoc  :%s\n",command->heredoc);
// printf("end  :%s\n",command->end_heredoc);
// return;
// return;


// void free_command(t_command *command){
//     free(command->name);
// }

void simple_command(t_command *command) {
    
    // printf("Command name :%s\n",command->name);
    // printf("Args :");
    // printf("\n");
    // printf("infile  :%s\n",command->infile);
    // printf("outfile  :%s\n",command->outfile);
    // printf("argc  :%d\n",command->argc);
    // printf("append_mode  :%s\n",command->append_mode);
    // printf("Heredoc  :%s\n",command->heredoc);
    // printf("end  :%s\n",command->end_heredoc);
    // return;
    int flags;
    flags = 0;
    
    int fd;
    char *str;
    
    str = to_lower(command->name);
    if(check_is_built_in(str)){
        char *lower;
        lower = to_lower(command->name);
        command->name = lower;
        free(lower);
        execute_built_in(command);
        flags = 1;
        free(str);
        return;
    }
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
    char *join;
    while (spliting[i] != NULL)
    {
        cmd = ft_strjoin(spliting[i],"/");
        join = ft_strjoin(cmd,command->name);
        if(!access(join,X_OK)){
            free(cmd);
            cmd = join;
            exec = 1;
            break;
        }
        free(join);
        free(cmd);
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
            execve(cmd,argv,environ);
        else
            execve(command->name,argv,environ);
    }
    else
        wait(NULL);
        free(cmd);
        free_things(spliting);
        free(str);
	    dup2(STDIN_FILENO, 1);
        free(command);
}