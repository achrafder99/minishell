/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/03/21 18:57:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void put(char *string){
		int i;
		i = 1;
		while(string[i] != '\0'){
				write(1,&string[i],1);
				i++;
		}
}

void ft_put_echo(t_tokens *tokens){
	t_tokens *node;
	node = tokens;
	
	while(node != NULL){
			char *string;
			string = node->token;
			while (*string != '\\' && *string != '\0')
			{
					write(1,string,1);
					string++;;
			}
			char **spliting;
			spliting = ft_split(string,'\\');
			int i;
			i = 0;
			while(spliting[i] != NULL){
				if(spliting[i][0] == 'n')
					write(1,"\n",1);
				if(spliting[i][0] == 't')
					write(1,"\t",1);
				if(spliting[i][0] == 'b')
					write(1,"\b",1);
				if(spliting[i][0] == 'r')
					write(1,"\r",1);
				if(spliting[i][0] == 'f')
					write(1,"\f",1);
				if(spliting[i][0] == 'a')
					write(1,"\a",1);
				if(spliting[i][0] == '\\')
					write(1,"\\",1);
				if(spliting[i][0] == '\'')
					write(1,"\'",1);
				if(spliting[i][0] == '\"')
					write(1,"\"",1);
				if(spliting[i][0] == '\?')
					write(1,"?",1);
				if(spliting[i][0] == 'v')
					write(1,"\v",1);
				put(spliting[i]);
				i++;
			}	
			node = node->next;
			write(1," ",1);
	}
}

int	get_length(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	echo(t_tokens *tokens)
{
	t_tokens *echo_command;
	echo_command = tokens->next;
	int flags;

	flags = 0;
	if(echo_command == NULL)
		return;
	while ( !ft_strcmp(echo_command->token,"-n") ){
				flags = 1;
				echo_command = echo_command->next;
				if(echo_command == NULL)
						break;
	}
	ft_put_echo(echo_command);
	if(!flags)
		write(1,"\n",1);
}