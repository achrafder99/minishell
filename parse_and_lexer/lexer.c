/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 01:42:51 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lex2(char **spliting, char *type, t_data *data)
{
	if (!ft_strcmp(spliting[0], ">>"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], "<<"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], ">"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], "<"))
		lex_redirection(data);
}

void	lex1(char **spliting, t_components **head, int i)
{
	t_data				data;
	int					flags;

	flags = 0;
	data = (t_data){.type = spliting[0], head, spliting, &i, &flags};
	lex2(spliting, data.type, &data);
	while (spliting[i] != NULL)
	{
		if (spliting[i][0] == '|')
			push_component(head, "PIPE", spliting, &i);
		else if (check_is_redirection(spliting[i]))
		{
			redirect_componenets(spliting, &i, head);
			if (spliting[i + 1] != NULL && !flags \
			&& !check_is_redirection(spliting[i + 1]))
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

void	lexer(char *input, t_components **head, t_info *info, t_env *env)
{
	char	**spliting;
	int		i;

	i = 0;
	spliting = split_input(input);
	if (check_is_redirection(spliting[0]))
		lex1(spliting, head, i);
	else
	{
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
	return (free_things(spliting), parser(*head, info,env));
}
