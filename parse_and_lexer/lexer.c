/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 01:01:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lex2(char **spliting, t_data *data)
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

void	token_lex1(char **spliting, int *i, t_components **head, t_info *info)
{
	if (!ft_strcmp(spliting[*i], "|"))
	{
		info->flags = 0;
		info->type = "PIPE";
		push_component(head, spliting, i, info);
	}
	else if (check_is_redirection(spliting[*i]))
	{
		redirect_componenets(spliting, i, head, info);
		if (spliting[*i + 1] != NULL && !info->flags
			&& !check_is_redirection(spliting[*i + 1])
			&& ft_strcmp(spliting[*i + 1], "|"))
		{
			push(head, spliting[*i + 1], "COMMAND");
			i++;
			info->flags = 1;
		}
	}
	else
		push(head, spliting[*i], "ARG");
	(*i)++;
}

void	lex1(char **spliting, t_components **head, int i, t_info *info)
{
	t_data	data;
	int		flags;

	flags = 0;
	info->flags = 0;
	data = (t_data){.type = spliting[0], head, spliting, &i, &info->flags};
	lex2(spliting, &data);
	while (spliting[i] != NULL)
		token_lex1(spliting, &i, head, info);
}

void	token_input(char **spliting, int *i, t_components **head, t_info *info)
{
	if (spliting[*i][0] == '-')
		push(head, spliting[*i], "OPTION");
	else if (!ft_strcmp(spliting[*i], "|"))
	{
		info->flags = 0;
		if (!check_is_redirection(spliting[*i + 1]) && spliting[*i + 1] != NULL
			&& ft_strcmp(spliting[*i + 1], "|"))
			info->flags = 1;
		info->type = "PIPE";
		push_component(head, spliting, i, info);
	}
	else if (check_is_redirection(spliting[*i]) && spliting[*i] != NULL)
		redirect_componenets(spliting, i, head, info);
	else
		push(head, spliting[*i], "ARG");
	(*i)++;
}

void	lexer(char *input, t_components **head, t_info *info, t_env *env)
{
	int		i;
	char	**spliting;

	i = 0;
	spliting = split_input(input);
	if (check_is_redirection(spliting[0]))
		lex1(spliting, head, i, info);
	else
	{
		push(head, spliting[0], "COMMAND");
		i = 1;
		while (spliting[i] != NULL)
			token_input(spliting, &i, head, info);
		if (!ft_strcmp(spliting[i - 1], "|") && !check_command_pipe(head))
		{
			if (open_pipe(head, info) == 258)
			{
				info->status_code = 258;
				return (free_things(spliting), free_node(*head));
			}
		}
	}
	return (free_things(spliting), expander(*head, env, info),
		free_node(*head));
}
