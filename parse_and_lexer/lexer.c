/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 01:29:24 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_input(char *input)
{
	char	*str;
	char	*error;
	char	**spliting;

	str = NULL;
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		spliting = ft_split(str, ' ');
	else
		spliting = ft_split(input, ' ');
	if (!check_quotes(input))
	{
		error = "Syntax Error: String must be closed\n";
		write(2, error, ft_strlen(error));
		return (NULL);
	}
	free(str);
	return (spliting);
}

void	push_component(t_components **head, char *type, char **spliting, int *i)
{
	if (!ft_strcmp(type, "PIPE"))
	{
		push(head, spliting[*i], "PIPE");
		if (spliting[*i + 1] != NULL)
		{
			push(head, spliting[*i + 1], "COMMAND");
			(*i)++;
		}
	}
	else if (!ft_strcmp(type, "REDIRECT_out"))
		out(spliting, i, head);
	else if (!ft_strcmp(type, "REDIRECT_in"))
		in(spliting, i, head);
	else if (!ft_strcmp(type, "APPEND_MODE"))
		append_mode(spliting, i, head);
	else
		here_doc(spliting, i, head);
}

void	lexer(char *input, t_components **head, t_info *info)
{
	char	**spliting;
	int		i;

	spliting = split_input(input);
	if (!spliting)
		return ;

	if(!ft_strcmp(spliting[0],"<<") || check_is_redirection(spliting[0]))
	{
		int flags;
		flags = 0;
		if(!ft_strcmp(spliting[0],"<<"))
		{
			push(head, spliting[0], "HEREDOC");
			if(spliting[1] != NULL)
				push(head, spliting[1], "END_HEREDOC");
			else if(spliting[2] != NULL)
				push(head, spliting[2], "COMMAND");
			i = 3;
			while (spliting[i] != NULL)
			{
				if(spliting[i][0] == '|')
					push_component(head, "PIPE", spliting, &i);
				else if(check_is_redirection(spliting[i]))
					redirect_componenets(spliting, &i, head);
				else
					push(head, spliting[i], "ARG");
				i++;
			}
		}
		else if (!ft_strcmp(spliting[0],">"))
		{	
			push(head, spliting[0], "REDIRECT_out");
			i = 1;
			if(spliting[1] != NULL && ft_strcmp(spliting[1],">")){
				push(head, spliting[1], "FILENAME");
				i += 1;
			}
			if(spliting[2] != NULL && ft_strcmp(spliting[2],">")){
				push(head, spliting[2], "COMMAND");
				i += 2;
			}
			while (spliting[i] != NULL)
			{
				if(spliting[i][0] == '|')
					push_component(head, "PIPE", spliting, &i);
				else if(check_is_redirection(spliting[i])){
					redirect_componenets(spliting, &i, head);
					if(spliting[i + 1] != NULL && !flags && !check_is_redirection(spliting[i + 1]))
						{
						push(head, spliting[i + 1], "COMMAND");
						i++;
						flags = 1;
					}
				}
				else
					push(head, spliting[i], "ARG");
				i++;
			}
		}
		else if (!ft_strcmp(spliting[0],"<"))
		{
			push(head, spliting[0], "REDIRECT_in");
			i = 1;
			if(spliting[1] != NULL && ft_strcmp(spliting[1],">"))
			{
				if(open(spliting[1],O_RDONLY,0777) == -1)
				{
					printf("tsh: %s",spliting[1]);
					printf(": No such file or directory\n");
					return;
				}
				push(head, spliting[1], "FILENAME");
				i += 1;
			}
			if(spliting[2] != NULL && ft_strcmp(spliting[2],">"))
			{
				push(head, spliting[2], "COMMAND");
				i += 2;
			}
			while (spliting[i] != NULL)
			{
				if(spliting[i][0] == '|')
					push_component(head, "PIPE", spliting, &i);
				else if(check_is_redirection(spliting[i])){
					redirect_componenets(spliting, &i, head);
					if(spliting[i + 1] != NULL && !flags && !check_is_redirection(spliting[i + 1]))
					{
						push(head, spliting[i + 1], "COMMAND");
						i++;
						flags = 1;
					}
				}
				else
					push(head, spliting[i], "ARG");
				i++;
			}
		}
		else if (!ft_strcmp(spliting[0],">>"))
		{
			push(head, spliting[0], "APPEND_MODE");
			i = 1;
			if(spliting[1] != NULL && ft_strcmp(spliting[1],">>")){
				push(head, spliting[1], "FILENAME");
				i += 1;
			}
			if(spliting[2] != NULL && ft_strcmp(spliting[2],">>")){
				push(head, spliting[2], "COMMAND");
				i += 2;
			}
			while (spliting[i] != NULL)
			{
				if(spliting[i][0] == '|')
					push_component(head, "PIPE", spliting, &i);
				else if(check_is_redirection(spliting[i])){
					redirect_componenets(spliting, &i, head);
					if(spliting[i + 1] != NULL  && !flags && !check_is_redirection(spliting[i + 1]))
					{
						push(head, spliting[i + 1], "COMMAND");
						i++;
						flags = 1;
					}
				}
				else
					push(head, spliting[i], "ARG");
				i++;
			}
		}
	}
	else{
		push(head, spliting[0], "COMMAND");
		i = 1;
		while (spliting[i] != NULL)
		{
			if (spliting[i][0] == '-')
				push(head, spliting[i], "OPTION");
			else if (spliting[i][0] == '|')
				push_component(head, "PIPE", spliting, &i);
			else if (check_is_redirection(spliting[i]))
				redirect_componenets(spliting, &i, head);
			else
				push(head, spliting[i], "ARG");
			i++;
		}
	}
	// free_things(spliting);
	parser(*head, info);
	// free_node(*head);
	*head = NULL;
}
