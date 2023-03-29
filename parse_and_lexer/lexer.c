/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 01:09:07 by adardour         ###   ########.fr       */
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

int check_is_space(char *input){
	int i;
	i = 0;
	int count;
	count = 0;
	while (input[i] != '\0')
	{
		if(includes(input[i]) && input[i + 1] != '>'){
			if(input[i + 1] != ' ' || input[i - 1] != ' ')
				count++;
		}
		else{
			if(input[i + 1] == '>'){
				count++;
				i += 2;
			}
		}
		i++;
	}
	return (count);
}

void	lexer(char *input, t_tokens **head,t_info *info)
{
	char	**spliting;
	int		i;
	int 	flags;
	char 	*str;

	str = NULL;
	if(check_is_space(input))
		str = new_str(input,check_is_space(input));
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
	i = 0;
	if(!ft_strcmp(spliting[0],"<<") || !ft_strcmp(spliting[0],">>") || !ft_strcmp(spliting[0],">") || !ft_strcmp(spliting[0],"<")){
		if(!ft_strcmp(spliting[0],"<<")){
			int j;
			j = 1;
			push(head, cut_string(ft_strtrim(spliting[0],"\'\"")), "HEREDOC");
			if(spliting[1] != NULL){
				push(head, cut_string(ft_strtrim(spliting[1],"\'\"")), "END_HEREDOC");
				j++;
			}
			if(spliting[2] != NULL){
				push(head, cut_string(ft_strtrim(spliting[2],"\'\"")), "COMMAND");
				j++;
			}
			while (spliting[j] != NULL)
			{
				if(spliting[j][0] == '-')
					push(head, spliting[j], "OPTION");
				else if(spliting[j][0] == '|'){
					push(head, spliting[j], "PIPE");
					if (spliting[j + 1] != NULL)
					{
						push(head, spliting[j + 1], "COMMAND");
						j++;
					}
				}
				else if(!ft_strcmp(spliting[j],"<<") \
				|| !ft_strcmp(spliting[j],">>") \
				|| !ft_strcmp(spliting[j],"<<") \
				|| !ft_strcmp(spliting[j],">") \
				|| !ft_strcmp(spliting[j],"<")){
					if(!ft_strcmp(spliting[j],"<<")){
						push(head, spliting[j], "HEREDOC");
						if (spliting[j + 1] != NULL)
						{
							push(head, spliting[j + 1], "END_HEREDOC");
							j++;
						}
					}
					else if (!ft_strcmp(spliting[j],"<"))
					{
						push(head, spliting[j], "REDIRECT_in");
						if (spliting[j + 1] != NULL)
						{
							push(head, spliting[j + 1], "FILENAME");
							j++;
						}
					}

					else if(!ft_strcmp(spliting[j],">"))
					{
						push(head, spliting[j], "REDIRECT_out");
						if (spliting[i + 1] != NULL)
						{
							push(head, spliting[j + 1], "FILENAME");
							j++;
						}
					}
					else{
						push(head, spliting[j], "APPEND_MODE");
						if (spliting[j + 1] != NULL)
						{
							push(head, spliting[j + 1], "FILENAME");
							j++;
						}
					}
				}
				else
					push(head, ft_strtrim(spliting[j],"\'\""), "ARG");
				j++;
			}
		}
	}
	// parser(*head,info);

	else{
		push(head, cut_string(ft_strtrim(spliting[0],"\'\"")), "COMMAND");
		i = 1;
		while (spliting[i] != NULL)
		{
			if (spliting[i][0] == '-')
				push(head, spliting[i], "OPTION");
			else if (spliting[i][0] == '|')
			{
				push(head, spliting[i], "PIPE");
				if (spliting[i + 1] != NULL)
				{
					push(head, spliting[i + 1], "COMMAND");
					i++;
				}
			}
			else if (!ft_strcmp(spliting[i],">>") || !ft_strcmp(spliting[i],"<<") || !ft_strcmp(spliting[i],">") || !ft_strcmp(spliting[i],"<"))
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
				else if(!ft_strcmp(spliting[i],">>")){
					push(head, spliting[i], "APPEND_MODE");
					if (spliting[i + 1] != NULL)
					{
						push(head, spliting[i + 1], "FILENAME");
						i++;
					}
				}
				else{
					push(head, spliting[i], "HEREDOC");
					if (spliting[i + 1] != NULL)
					{
						push(head, spliting[i + 1], "END_HEREDOC");
						i++;
					}
				}
			}
			else
				push(head, ft_strtrim(spliting[i],"\'\""), "ARG");
			i++;
			}
	}
	parser(*head,info);
	i = 0;
	while (spliting[i] != NULL)
	{
		free(spliting[i]);
		i++;
	}
	free(spliting);
	spliting = NULL;
}