/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/03/26 23:06:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals(int sign){
    char *username;
    char *full_username;

    username = ft_strjoin(getenv("USER"), "@:");
    full_username = ft_strjoin(username, "user > ");
    if (sign == SIGINT){
        write(1,"\n",1);
        write(1,full_username,ft_strlen(full_username));
    }
    free(username);
    free(full_username);
}

char *display_name(){
    char *username;
    char *full_username;
    char *temp;

    username = ft_strjoin(getenv("USER"), "@:");
    temp = username;
    free(username);
    // full_username = ft_strjoin(BLUE, "➜  ");
    // full_username = ft_strjoin(BLUE, ft_strjoin(full_username, username));
    // full_username = ft_strjoin(full_username, " > ");
    // full_username = ft_strjoin(full_username, RESET);
    if (username == NULL){
        write(2, "Could not get username", ft_strlen("Could not get username"));
        exit(EXIT_FAILURE);
    }
    char *dd;
    dd = ft_strjoin(temp," > ");
    free(username);
    username = NULL;
    return (dd);
}

int main(int argc, char **argv, char **envp)
{	
    t_tokens *head;
    char *input;

    head = NULL;
    char *full_username;
    signal(SIGINT,handle_signals);
    while (1)
    {
        full_username = display_name();
        char *tt;
        tt = ft_strjoin(full_username,"");
        input = readline(tt);
        if (input == NULL){
            write(1, " ", 1);
            write(1, "exit\n", 5);
            free(full_username);
            full_username = NULL;
            exit(1);
        }
        else if (strlen(input) == 0){
            printf("here\n");
            free(input);
            free(full_username);
            tt = NULL;
            continue;
        }
        lexer(input, &head);
        add_history(input);
        free(input);
        input = NULL;
        while (head)
        {
            free(head->token);
            free(head->type.type);
            head->token = NULL;
            head->type.type = NULL;
            head = head->next;
        }
        free(head);
    }
}