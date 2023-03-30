/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:31:26 by adardour          #+#    #+#             */
/*   Updated: 2023/03/30 01:49:11 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_errors(t_components *tokens){

    t_components *node;
    node = tokens;
    while(node != NULL){
		if(node == NULL)
			break;
		if(!ft_strcmp(node->type.type,"PIPE")){
			if(node->next == NULL || !ft_strcmp(node->next->token,"|")){
				char *error;
				error = "parse error :Pipe must be followed by Command\n",
				write(2,error,ft_strlen(error));
				return (1);
			}
			if(ft_strcmp(node->next->type.type,"COMMAND")){
				char *error;
				error = "parse error :Pipe must be followed by Command\n",
				write(2,error,ft_strlen(error));
				return (1);
			}
		}
		else if(!ft_strcmp(node->type.type,"REDIRECT_in") \
		|| !ft_strcmp(node->type.type,"REDIRECT_out") \
		|| !ft_strcmp(node->type.type,"APPEND_MODE") \
		|| !ft_strcmp(node->type.type,"HEREDOC")){
			if(!ft_strcmp(node->type.type,"REDIRECT_out")){
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return (1);
				}
			}
			else if(!ft_strcmp(node->type.type,"REDIRECT_in")){
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return (1);
				}
			}
			else if(!ft_strcmp(node->type.type,"APPEND_MODE")){
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return (1);
				}
			}
			else{
				if(node->next == NULL){
					char *error;
					error = "tash: syntax error near unexpected token `newline'\n",
					write(2,error,ft_strlen(error));
					return (1);
				}
			}
		}
		node = node->next;
	}
	// free_node(node);
    return (0);
}