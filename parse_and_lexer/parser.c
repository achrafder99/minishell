/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 22:01:54 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parser(t_components *tokens,t_info *info){

	t_components *node;
	node = tokens;
	// while (node != NULL)
	// {
	// 	printf("Token (%s) Type (%s)\n",node->token,node->type.type);
	// 	node = node->next;
	// }
	// return;

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
	if(!ft_strcmp(node->type.type,"HEREDOC") || !ft_strcmp(node->type.type,"COMMAND")){
		command = (t_command*) malloc(sizeof(t_command));
		command->name = node->token;
		command->argc = 0;
		command->args = NULL;
		command->infile = NULL;
		command->outfile = NULL;
		command->append_mode = NULL;
		command->heredoc = NULL;
		command->end_heredoc = NULL;
		if(!ft_strcmp(node->type.type,"HEREDOC"))
			dd = 1;
	}
	while (node != NULL) {
		if (!ft_strcmp(node->type.type,"COMMAND") && dd == 0) {
			if (check_command(node->token) \
			|| 	check_is_built_in(node->token) \
			|| 	access(node->token,F_OK) != -1 \
			|| 	!ft_strcmp(node->token,"<<") \
			||  !ft_strcmp(node->token,">") \
			|| 	!ft_strcmp(node->token,"<") \
			|| 	!ft_strcmp(node->token,">>")) {
				command = (t_command*) malloc(sizeof(t_command));
				command->name = node->token;
				command->argc = 0;
				command->args = NULL;
				command->infile = NULL;
				command->outfile = NULL;
				command->append_mode = NULL;
				command->heredoc = NULL;
				command->end_heredoc = NULL;
			}
			else {
				char *error = ft_strjoin(node->token, " :Command not found\n");
				write(2, error, ft_strlen(error));
				return;
			}
		}
		if (!ft_strcmp(node->type.type,"OPTION") || !ft_strcmp(node->type.type,"ARG")) {
			command->argc += 1;
			char** new_args = (char**) malloc((command->argc + 1) * sizeof(char*));
			if (command->args) {
				ft_memcpy(new_args, command->args, (command->argc - 1) * sizeof(char*));
				free(command->args);
			}
			new_args[command->argc - 1] = cut_string(node->token);
			new_args[command->argc] = NULL;
			command->args = new_args;
		}	
		if (!ft_strcmp(node->type.type,"REDIRECT_in") \
		|| !ft_strcmp(node->type.type,"REDIRECT_out") \
		|| !ft_strcmp(node->type.type,"APPEND_MODE") \
		|| !ft_strcmp(node->type.type,"HEREDOC")) {
			if (!ft_strcmp(node->type.type,"REDIRECT_in"))
				command->infile = node->next->token;
			else if(!ft_strcmp(node->type.type,"REDIRECT_out"))
				command->outfile = node->next->token;
			else if(!ft_strcmp(node->type.type,"APPEND_MODE"))
				command->append_mode = node->next->token;
			else{
				command->heredoc = node->token;
				command->end_heredoc = node->next->token;
			}
		}
		if (!ft_strcmp(node->type.type,"PIPE")) {
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
				
				new_commands[pipe_line->number_of_commands - 1] = *command;
				pipe_line->command = new_commands;
			}
		}
    	node = node->next;    
	}
	if (command != NULL) {
        if (!pipe_line) 
			simple_command(command);
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