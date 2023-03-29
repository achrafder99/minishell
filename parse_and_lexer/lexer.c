/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 21:25:18 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(char *input, t_components **head,t_info *info)
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
	if(!ft_strcmp(spliting[0],"<<") \
	|| !ft_strcmp(spliting[0],">>") \
	|| !ft_strcmp(spliting[0],">") \
	|| !ft_strcmp(spliting[0],"<")){
		
	}
	else{
		push(head, spliting[0], "COMMAND");
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
			else if (!ft_strcmp(spliting[i],">>") \
			|| !ft_strcmp(spliting[i],"<<") 
			|| !ft_strcmp(spliting[i],">") 
			|| !ft_strcmp(spliting[i],"<"))
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
				push(head, spliting[i], "ARG");
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