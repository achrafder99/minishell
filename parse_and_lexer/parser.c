/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/04/02 04:36:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    display_error(char *cut_str,t_command *command){
    char *error = ft_strjoin(cut_str, " :Command not found\n");
    write(2, error, ft_strlen(error));
    free(error);
    free(command);
    free(cut_str);
}

char* handle_command(t_components *node, t_command **command) {
    char *cut_str = cut_string(node->token);
    if (!ft_strcmp(node->type.type,"COMMAND")) {
        if (check_command(cut_str) \
        || check_is_built_in(cut_str) \
        || access(cut_str,F_OK) != -1 )
            *command = init_command(*command, cut_str);
        else {
            display_error(cut_str, *command);
            return ("404");
        }
    }
    else if (!ft_strcmp(node->type.type,"OPTION") || !ft_strcmp(node->type.type,"ARG"))
        (*command)->args = add_args(*command, cut_str);
    else if (check_type(node->type.type))
    {
        if(!ft_strcmp(node->type.type,"REDIRECT_in")){
            if(open_in(*command, node->next->token) == -1)
                return ("ERROR_OPEN");
        }
        else if(!ft_strcmp(node->type.type,"REDIRECT_out")){
            (*command)->outfile = cut_string(node->next->token);
            int fd = open((*command)->outfile, O_RDONLY | O_CREAT, 0777);
            close(fd);
        }
        else if(!ft_strcmp(node->type.type,"APPEND_MODE")){
            (*command)->append_mode = node->next->token;
            int fd = open((*command)->append_mode, O_CREAT, 0777);
            close(fd);
        }
        else{
            (*command)->heredoc = cut_str;
            (*command)->end_heredoc = node->next->token;
        }
    }
    return ("SUCCESS");
}

void handle_pipe(t_components *node, t_piped **pipe_line, t_command **command) {
    int pipe = 0;
    if (!ft_strcmp(node->type.type,"PIPE")) {
        pipe = 1;
        if (!*pipe_line) {
            *pipe_line = malloc(sizeof(t_piped));
            if (!*pipe_line)
                return;
            (*pipe_line)->number_of_commands = 1;
            (*pipe_line)->command = malloc(sizeof(t_command));
            if(!(*pipe_line)->command){
                exit(1);
                return;
            }
            (*pipe_line)->command[0] = **command;
        }
        else {
            (*pipe_line)->number_of_commands++;
            t_command* new_commands = (t_command*) malloc((*pipe_line)->number_of_commands * sizeof(t_command));
            if(!new_commands){
                exit(1);
                return;
            }
            if ((*pipe_line)->command) {
                ft_memcpy(new_commands, (*pipe_line)->command, ((*pipe_line)->number_of_commands-1) * sizeof(t_command));
                free((*pipe_line)->command);
            }
            new_commands[(*pipe_line)->number_of_commands - 1] = **command;
            (*pipe_line)->command = new_commands;
        }
    }
}


void parser(t_components *tokens,t_info *info)
{
    t_components *node = tokens;
    int fd;
    t_command* command = NULL;
    t_piped *pipe_line = NULL;
    if(handle_errors(tokens))
        return;
    if(check_option(node))
        return;
    while (node != NULL) {
        char *status;
        status = handle_command(node, &command);
        if(!ft_strcmp(status,"404") || !ft_strcmp(status,"ERROR_OPEN"))
             return ;
        handle_pipe(node, &pipe_line, &command);
        node = node->next;
    }
    if (command != NULL)
        piped(pipe_line, command);
}
