/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/03/25 02:12:57 by adardour         ###   ########.fr       */
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

void print_command(t_command *command){
	t_command *cmd;
	cmd = command;	
	printf("Command name :%s\n",cmd->name);
	int i = 0;
	char **args = cmd->args;
	if(args != NULL){
		while (args[i] != NULL)
		{	
			printf("%s ",args[i]);
			i++;
		}
	}
	printf("Number of Argument name :%d\n",cmd->argc);
	printf("infile name :%s\n",cmd->infile);
	printf("outfile name :%s\n",cmd->outfile);
}

char **get_full_args(t_tokens *tokens,char *start){
	char **full_args;

	t_tokens *nodes;
	nodes = tokens;
	// while (nodes != NULL){
	// 	printf("%s\n",nodes->token);
	// 	nodes = nodes->next;
	// }
	// while ((!ft_strcmp(nodes->type.type,"OPTION") || !ft_strcmp(nodes->type.type,"ARG")) && (nodes != NULL))
	// {
	// 	printf("%s\n",nodes->token);
	// 	nodes = nodes->next;
	// }
	
	return (full_args);
}

void parser(t_tokens *tokens){

	t_tokens *node;
	node = tokens;
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
		else if(!ft_strcmp(node->type.type,"REDIRECT_in") || !ft_strcmp(node->type.type,"REDIRECT_out")){
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
		}
		node = node->next;
	}
	t_command *command;
	t_piped *pipe_line;
	node = tokens;
	while(node){
		if(!ft_strcmp(node->type.type,"COMMAND")){
			if(!access(ft_strjoin("/bin/",node->token), X_OK))
			{
					command = (t_command*) malloc(sizeof(t_command));
					command->name = tokens->token;
					command->argc = 0;
					command->args = NULL;
					command->infile = NULL;
					command->outfile = NULL;
			}
			else
			{
					char *error;
					error = ft_strjoin(node->token," :Command not found\n");
					write(2,error,ft_strlen(error));
					return;
			}
		}
		else if(!ft_strcmp(node->type.type,"OPTION") || !ft_strcmp(node->type.type,"ARG")){
			command->argc += 1;
			// command->args = get_full_args(node,tokens->token);
			printf("%s\n",node->token);
		}
		node = node->next;	
	}
	print_command(command);
}