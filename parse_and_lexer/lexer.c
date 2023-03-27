/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 05:01:21 by adardour         ###   ########.fr       */
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

int includes(char car){
	char *dd[] = {"|",">","<",NULL};
	int i;
	i = 0;
	if(car == '|' || car == '>' || car == '<')
		return (1);
	i++;
	return (0);
}

int check_is_space(char *input){
	int i;
	i = 0;
	int count;
	count = 0;
	while (input[i] != '\0')
	{
		if(includes(input[i])){
			if(input[i + 1] != ' ' || input[i - 1] != ' ')
				count++;
		}
		i++;
	}
	return (count);
}

char *new_str(char *str,int count){
	int i;
	i = 0;

	int j;
	j = 0;
	
	char *new_str;
	int length = ft_strlen(str) + count * 2;
	new_str = malloc(length + 1);
	while (i < length - 1)
	{
		if(includes(str[i])){
			if(includes(str[i])){
				new_str[j] = ' ';
				j++;
				new_str[j] = str[i];
				j++;
				new_str[j] = ' ';
			}
		}
		else
			new_str[j] = str[i];
		i++;
		j++;
	}

	return (new_str);
}

void	lexer(char *input, t_tokens **head)
{
	char	**spliting;
	int		i;
	int 	flags;
	char 	*str;

	str = NULL;
	if(check_is_space(input)){
		str = new_str(input,check_is_space(input));
		printf("%s\n",str);
	}
	if(str)
		spliting = ft_split(str, ' ');
	else
		spliting = ft_split(input, ' ');
	if(!check_quotes(input)){
		char *error;
		error = "Syntax Error:  String must be Closed\n";
		write(2,error,ft_strlen(error));
		return;
	}
	push(head, cut_string(ft_strtrim(spliting[0],"\'\"")), "COMMAND");
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
			push(head, ft_strtrim(spliting[i],"\'\""), "ARG");
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