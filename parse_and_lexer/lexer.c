/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/25 17:32:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quotes(char *input){
	int i;
	i = 0;
	int single;
	int double_q;
	single  = 0;
	double_q  = 0;
	while (input[i] != '\0')
	{
		if((input[i] == '\'' || input[i] == '\"') && input[i - 1] != '\\'){
			if(input[i] == '\'')
					single++;
			else
				double_q++;
		}
		i++;
	}
	if(single % 2 != 0 || double_q % 2 != 0)
			return (0);
	return (1);
}

void	lexer(char *input, t_tokens **head)
{
	char	**spliting;
	int		i;

	if(!check_quotes(input)){
		char *error;
		error = "Syntax Error:  String must be Closed\n";
		write(2,error,ft_strlen(error));
		return;
	}
	spliting = ft_split(input, ' ');
	push(head, spliting[0], "COMMAND");
	i = 1;
	while (spliting[i] != NULL)
	{
		if (spliting[i][0] == '-'){
			push(head, spliting[i], "OPTION");
		}
		else if (spliting[i][0] == '|')
		{
			push(head, spliting[i], "PIPE");
			if (spliting[i + 1] != NULL)
			{
				push(head, spliting[i + 1], "COMMAND");
				i++;
			}
		}
		else if (!ft_strcmp(spliting[i],">>") || !ft_strcmp(spliting[i],">") || !ft_strcmp(spliting[i],"<"))
		{
			if (!ft_strcmp(spliting[i],"<"))
			{
				push(head, spliting[i], "REDIRECT_in");
				if (spliting[i + 1] != NULL)
				{
					push(head, spliting[i + 1], "FILENAME");
					i++;
				}
			}
			else if(!ft_strcmp(spliting[i],">"))
			{
				push(head, spliting[i], "REDIRECT_out");
				if (spliting[i + 1] != NULL)
				{
					push(head, spliting[i + 1], "FILENAME");
					i++;
				}
			}
			else{
				push(head, spliting[i], "APPEND_MODE");
				if (spliting[i + 1] != NULL)
				{
					push(head, spliting[i + 1], "FILENAME");
					i++;
				}
			}
		}
		else if (spliting[i][0] == '$')
			push(head, spliting[i], "ENV");
		else
			push(head, spliting[i], "ARG");
		i++;
	}
	parser(*head);
	i = 0;
	while (spliting[i] != NULL)
	{
		free(spliting[i]);
		i++;
	}
	free(spliting);
	spliting = NULL;
	
}