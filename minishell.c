/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/03/25 18:04:45 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signals(int sign){
	char		*username;
	char		*full_username;

	username = ft_strjoin(getenv("USER"), "@:");
	full_username = ft_strjoin(username, "user > ");
    if(sign == SIGINT){
		write(1,"\n",1);
		write(1,full_username,ft_strlen(full_username));
	}
}

int main(int argc, char **argv, char **envp)
{	
    char *username;
    t_tokens *head;
    char *input;
    char *full_username;

    head = NULL;
    username = ft_strjoin(getenv("USER"), "@:");
	full_username = ft_strjoin(BLUE, "➜  ");
    full_username = ft_strjoin(BLUE, ft_strjoin(full_username,username));
    full_username = ft_strjoin(full_username, " > ");
    full_username = ft_strjoin(full_username, RESET);
    if (username == NULL)
    {
        write(2, "Could not get username", ft_strlen("Could not get username"));
        exit(EXIT_FAILURE);
    }
    signal(SIGINT,handle_signals);
    while (1)
    {
        input = readline(full_username);
        if (input == NULL){
            write(1,"\n",1);
            write(1,"exit\n",5);
            exit(1);
        }
        if (strlen(input) == 0)
            continue ;
        add_history(input);
        lexer(input, &head);
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
        free(username);
        username = NULL;
    }
    free(username);
    username = NULL;
}