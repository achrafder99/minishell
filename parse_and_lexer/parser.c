/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 00:50:03 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_is_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

void free_things(char **spliting){
	int i;
	i = 0;
	while (spliting[i])
	{
		free(spliting[i]);
		i++;
	}
	free(spliting);
	spliting = NULL;
}

int check_command(char *command){

	char *path;
	path = getenv("PATH");
	char **spliting;
	char *full_command;
	spliting = ft_split(path,':');
	int i;
	i = 0;
	while (spliting[i] != NULL)
	{
		full_command = ft_strjoin(spliting[i],ft_strjoin("/",command));
		if(!access(full_command,X_OK)){
			free_things(spliting);
			spliting = NULL;
			free(full_command);
			full_command = NULL;
			return (1);
		}
		i++;
	}
	free_things(spliting);
	free(full_command);
	spliting = NULL;
	return (0);
}

void execute_pipe(t_piped *pipe) {
    printf("Number of commands: %d\n", pipe->number_of_commands);
    for (int i = 0; i < pipe->number_of_commands; i++) {
        printf("Command (%d): %s\n", i, pipe->command[i].name);
    }
}

void execute_built_in(t_command *cmd){
	if(!ft_strcmp(cmd->name,"cd"))
		cd(cmd);
	else if(!ft_strcmp(cmd->name,"pwd")){
		pwd(cmd);
	}
}

char **get_argv(t_command *command,int number_arg){
	char **argv;

	argv = malloc(sizeof(char*) * number_arg + 2);
	argv[0] = command->name;
	int i;
	i = 1;
	int j;
	j = 0;
	while (i <= number_arg)
	{
		argv[i] = command->args[j];
		i++;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

void simple_command(t_command *command) {
	
	if(check_is_built_in(command->name)){
		execute_built_in(command);
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

void parser(t_tokens *tokens){
	t_tokens *node;
	node = tokens;
	int pipe;
	pipe = 0;
	while(node != NULL){
		if(node == NULL)
			return;
		if(!ft_strcmp(node->type.type,"PIPE")){
			if(node->next == NULL){
				char *error;
				error = "parse error :Pipe must be followed by Command\n",
				write(2,error,ft_strlen(error));
				return;
			}
			if(ft_strcmp(node->next->type.type,"COMMAND")){
				char *error;
				error = "parse error :Pipe must be followed by Command\n",
				write(2,error,ft_strlen(error));
				return;
			}
		}
		else if(!ft_strcmp(node->type.type,"REDIRECT_in") || !ft_strcmp(node->type.type,"REDIRECT_out") || !ft_strcmp(node->type.type,"APPEND_MODE")){
			if(!ft_strcmp(node->type.type,"REDIRECT_out")){
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return;
				}
			}
			else if(!ft_strcmp(node->type.type,"REDIRECT_in")){
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return;
				}
			}
			else{
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return;
				}
			}
		}
		node = node->next;
	}
	t_command *command;
	t_piped *pipe_line;
	command = NULL;
	pipe_line = NULL;
	node = tokens;
	while (node) {
    if (!ft_strcmp(node->type.type,"COMMAND")) {
        if (check_command(node->token) || check_is_built_in(node->token)) {
            command = (t_command*) malloc(sizeof(t_command));
            command->name = node->token;
            command->argc = 0;
            command->args = NULL;
            command->infile = NULL;
            command->outfile = NULL;
            command->append_mode = NULL;
        }
        else {
            char *error = ft_strjoin(node->token, " :Command not found\n");
            write(2, error, ft_strlen(error));
            return;
        }
    }
	else if (!ft_strcmp(node->type.type,"OPTION") || !ft_strcmp(node->type.type,"ARG")) {
    command->argc += 1;
    char** new_args = (char**) malloc((command->argc + 1) * sizeof(char*));
    if (command->args) {
        ft_memcpy(new_args, command->args, (command->argc - 1) * sizeof(char*));
        free(command->args);
    }
    new_args[command->argc - 1] = node->token;
    new_args[command->argc] = NULL;
    command->args = new_args;
}	
    else if (!ft_strcmp(node->type.type,"REDIRECT_in") || !ft_strcmp(node->type.type,"REDIRECT_out") || !ft_strcmp(node->type.type,"APPEND_MODE")) {
        if (!ft_strcmp(node->type.type,"REDIRECT_in"))
            command->infile = node->next->token;
        else if(!ft_strcmp(node->type.type,"REDIRECT_out"))
            command->outfile = node->next->token;
		else
			command->append_mode = node->next->token;
    }
    else if (!ft_strcmp(node->type.type,"PIPE")) {
		pipe = 1;
		if (!pipe_line) {
			pipe_line = malloc(sizeof(t_piped));
			if (!pipe_line) 
				return;
			pipe_line->number_of_commands = 1;
			pipe_line->command = malloc(sizeof(t_command));
			pipe_line->command[0] = *command;
		}
		else {
			pipe_line->number_of_commands++;
			t_command* new_commands = (t_command*) malloc(pipe_line->number_of_commands * sizeof(t_command));
			if (pipe_line->command) {
				memcpy(new_commands, pipe_line->command, (pipe_line->number_of_commands-1) * sizeof(t_command));
				free(pipe_line->command);
			}
			new_commands[pipe_line->number_of_commands-1] = *command;
			pipe_line->command = new_commands;
		}
	}
    node = node->next;    
}
	if (command != NULL) {
        if (!pipe_line) {
			simple_command(command);
		}
        else {
            pipe_line->number_of_commands++;
            t_command* new_commands = (t_command*) malloc(pipe_line->number_of_commands * sizeof(t_command));
            if (pipe_line->command) {
                ft_memcpy(new_commands, pipe_line->command, (pipe_line->number_of_commands-1) * sizeof(t_command));
                free(pipe_line->command);
            }
            new_commands[pipe_line->number_of_commands - 1] = *command;
            pipe_line->command = new_commands;
            execute_pipe(pipe_line);
        }
    }
}