/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/04/07 00:44:05 by aalami           ###   ########.fr       */
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

int	check_is_redirection(char *symbol)
{
	return (!ft_strcmp(symbol, "<<")
		|| !ft_strcmp(symbol, ">>")
		|| !ft_strcmp(symbol, "<")
		|| !ft_strcmp(symbol, ">"));
}

void	lexer(char *input, t_components **head, t_info *info, t_lst *env, t_lst *exp, int child)
{
	char	**spliting;
	int		i;

	spliting = split_input(input);
	if (!spliting)
		return ;
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
	free_things(spliting);
	parser(*head, info, env, exp, child);
	free_node(*head);
	*head = NULL;
}
