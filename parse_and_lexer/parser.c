/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/04/01 22:22:16 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parser(t_components *tokens,t_info *info){
	
	t_components *node;
	node = tokens;
	
	int fd;
	t_command* new_commands;
	int dd;
	dd = 0;
	int pipe;
	pipe = 0;
	if(handle_errors(tokens))
		return;
	node = tokens;
	t_command *command;
	t_piped *pipe_line;
	command = NULL;
	pipe_line = NULL;
	node = tokens;
	char** new_args;
	char *cut_str;
	if(check_option(node))
		return;
	while (node != NULL) {
		cut_str = cut_string(node->token);
		if (!ft_strcmp(node->type.type,"COMMAND")) {
			if (check_command(cut_str) \
			|| 	check_is_built_in(cut_str) \
			|| 	access(cut_str,F_OK) != -1 \
			|| 	!ft_strcmp(cut_str,"<<") \
			||  !ft_strcmp(cut_str,">") \
			|| 	!ft_strcmp(cut_str,"<") \
			|| 	!ft_strcmp(cut_str,">>")) {
				command = (t_command*) malloc(sizeof(t_command));
				if(!command){
					return;
					exit(1);
				}
				command->name = cut_str;
				command->argc = 0;
				command->args = NULL;
				command->infile = NULL;
				command->outfile = NULL;
				command->append_mode = NULL;
				command->heredoc = NULL;
				command->end_heredoc = NULL;
			}
			else {
				char *error = ft_strjoin(cut_str, " :Command not found\n");
				write(2, error, ft_strlen(error));
				free(error);
				free(command);
				free(cut_str);
				return;
			}
		}
		else if (!ft_strcmp(node->type.type,"OPTION") || !ft_strcmp(node->type.type,"ARG")) {
			command->argc += 1;
			new_args = (char**) malloc((command->argc + 1) * sizeof(char*));
			if (command->args) {
				ft_memcpy(new_args, command->args, (command->argc - 1) * sizeof(char*));
				free(command->args);
			}
			new_args[command->argc - 1] = cut_str;
			new_args[command->argc] = NULL;
			command->args = new_args;
		}	
		else if (!ft_strcmp(node->type.type,"REDIRECT_in") \
		|| !ft_strcmp(node->type.type,"REDIRECT_out") \
		|| !ft_strcmp(node->type.type,"APPEND_MODE") \
		|| !ft_strcmp(node->type.type,"HEREDOC")) {
			if (!ft_strcmp(node->type.type,"REDIRECT_in")){
				command->infile = node->next->token;
				fd = open(command->infile, O_RDONLY,0777);
				if(fd == -1){
					char *error;
					error = ": No such file or directory\n";
					write(2,command->infile,ft_strlen(command->infile));
					write(2,error,ft_strlen(error));
					return;
				}
			}
			else if(!ft_strcmp(node->type.type,"REDIRECT_out")){
				command->outfile = cut_string(node->next->token);
				fd = open(command->outfile, O_CREAT,0777);
			}
			else if(!ft_strcmp(node->type.type,"APPEND_MODE"))
				command->append_mode = node->next->token;
			else{
				command->heredoc = cut_str;
				command->end_heredoc = node->next->token;
			}
		}
		else if (!ft_strcmp(node->type.type,"PIPE")) {
			pipe = 1;
			if (!pipe_line) {
				pipe_line = malloc(sizeof(t_piped));
				if (!pipe_line) 
					return;
				pipe_line->number_of_commands = 1;
				pipe_line->command = malloc(sizeof(t_command));
				if(!pipe_line->command){
					exit(1);
					return;
				}
				pipe_line->command[0] = *command;
			}
			else {
				pipe_line->number_of_commands++;
				new_commands = (t_command*) malloc(pipe_line->number_of_commands * sizeof(t_command));
				if(!new_commands){
					exit(1);
					return;
				}
				if (pipe_line->command) {
					ft_memcpy(new_commands, pipe_line->command, (pipe_line->number_of_commands-1) * sizeof(t_command));
					free(pipe_line->command);
				}
				new_commands[pipe_line->number_of_commands - 1] = *command;
				pipe_line->command = new_commands;
			}
		}
    	node = node->next; 
	}
	if (command != NULL) {
        if (!pipe_line) {
			simple_command(command);
			if(command->argc > 0)
				free_things(command->args);
			close(fd);
			return;
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
			return;
        }
    }
}