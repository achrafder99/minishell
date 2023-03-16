/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/16 20:55:05 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void parser(t_tokens* head) {
    char *command;
    command = ft_strjoin("/bin/",head->token);
    if(access(command,X_OK) != 0)
    {
        char *err;
        err = "command not found: ";
        write(2,err,ft_strlen(err));
        write(2,head->token,ft_strlen(head->token));
        write(2,"\n",1);
        
    }
    else{
        printf("Start Parsing\n");
    }
}
void lexer(char* input, t_tokens** head) {
    
    char **spliting;
    spliting = ft_split(input,' ');
    push(head,spliting[0],"COMMAND");
    int i;
    i = 1;
    while (spliting[i] != NULL)
    {
        if(spliting[i][0] == '-')
            push(head,spliting[i],"OPTION");
        else if(spliting[i][0] == '|'){
            push(head,spliting[i],"PIPE");
            if(spliting[i + 1] != NULL)
            {
                push(head,spliting[i + 1],"COMMAND");
                i++;
            }
        }
        else if(spliting[i][0] == '>' || spliting[i][0] == '<')
        {
            if(spliting[i][0] == '<')
            {
                push(head,spliting[i],"REDIRECT_in");
                if(spliting[i + 1] != NULL){
                    push(head,spliting[i + 1],"FILENAME");    
                    i++;   
                }      
            }  
            else{
                push(head,spliting[i],"REDIRECT_out");
                if(spliting[i + 1] != NULL){
                    push(head,spliting[i + 1],"FILENAME");    
                    i++;   
                }    
            }
        }
        else if(spliting[i][0] == '$')
            push(head,spliting[i],"ENV");
        else
            push(head,spliting[i],"ARG");
        i++;
    }
    parser(*head);
}
