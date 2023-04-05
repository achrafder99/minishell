/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:53 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 20:48:21 by adardour         ###   ########.fr       */
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

char* handle_command(t_components *node, t_command **command) 
{
    char *cut_str;
    cut_str = cut_string(node->token);
    if (!ft_strcmp(node->type.type,"COMMAND")) 
    {
        // if (check_command(cut_str) 
        // // check_is_built_in(cut_str)
        //     && access(cut_str,X_OK) != -1)
            *command = init_command(*command, cut_str);
        // else
        // {
        //     display_error(cut_str, *command);
        //     return ("404");
        // }
    }
    else if (!ft_strcmp(node->type.type,"OPTION") \
        || !ft_strcmp(node->type.type,"ARG"))
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

void handle_pipe(t_components *node, t_piped **pipe_line, t_command **command) 
{
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
            t_command* new_commands = (t_command*) \
            malloc((*pipe_line)->number_of_commands * \
            sizeof(t_command));
            if(!new_commands)
            {
                exit(1);
                return;
            }
            if ((*pipe_line)->command)
            {
                ft_memcpy(new_commands, (*pipe_line)->command, \
                ((*pipe_line)->number_of_commands -1) * \
                sizeof(t_command));
                free((*pipe_line)->command);
            }
            new_commands[(*pipe_line)->number_of_commands - 1] = **command;
            (*pipe_line)->command = new_commands;
        }
    }
}

int check_is_command(t_components *tokens)
{
    t_components *node;
    node = tokens;   
    while (node)
    {
        if(!ft_strcmp(node->type.type,"COMMAND"))
            return (1) ;
        node = node->next;
    }
    return (0);   
}

void parser(t_components *tokens,t_info *info)
{   
    return;
    t_components *node;
    node = tokens;
    // while (node != NULL) 
    // {
    //     printf("Token (%s) Type (%s)\n",node->token,node->type.type);
    //     node = node->next;
    // }
    // return;
    int fd;
    t_command* command = NULL;
    t_piped *pipe_line = NULL;
    if(handle_errors(tokens))
        return;
    if(check_option(node))
        return;
    if (check_is_command(node) && check_is_redirection(node->token))
    {
        t_components *goal;
        t_components *temp;
        
        if (tokens == NULL) 
        {
            tokens = temp;
            return;
        }
        goal = tokens;
        while (goal != NULL && ft_strcmp(goal->type.type, "COMMAND") != 0)
            goal = goal->next;
        if (goal != NULL)
        {
            temp = goal; 
            delete_node_by_type(&tokens, "COMMAND"); 
            ft_lstadd_front(&tokens, temp);
        }
        node = tokens;
    }
    if(!check_is_command(node) && check_is_redirection(node->token))
    {
        if (!ft_strcmp(node->type.type,"REDIRECT_out"))
        {
            while (node != NULL)
            {
                if(!ft_strcmp(node->type.type,"FILENAME"))
                    fd = open(node->token,O_RDWR | O_CREAT | O_TRUNC,0777);
                node = node->next;
                close(fd);
            } 
        }
        if(!ft_strcmp(tokens->type.type,"REDIRECT_in"))
        {
            fd = open(tokens->next->token,O_RDONLY,0777);
            if(fd == -1){
                printf("tsh: %s",tokens->next->token);
                printf(": No such file or directory\n");
                return;
            }
            close(fd);
        }
        if(!ft_strcmp(tokens->type.type,"APPEND_MODE"))
        {
            while (node != NULL)
            {
                if(!ft_strcmp(node->type.type,"FILENAME"))
                    fd = open(node->token,O_RDWR | O_CREAT | O_APPEND,0777);
                node = node->next;
                close(fd);
            } 
        }
    }
    else
    {
        while (node != NULL) 
        {
            char *status;
            status = handle_command(node, &command);
            // if(!ft_strcmp(status,"404") || \
            // !ft_strcmp(status,"ERROR_OPEN"))
            //     return ;
            handle_pipe(node, &pipe_line, &command);
            node = node->next;
        }
        if (command != NULL)
            piped(pipe_line, command);
    }
}
