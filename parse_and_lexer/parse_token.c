/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:29:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/31 13:12:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	deleteposition(t_components **head, int n)
{
	t_components	*temp;
	t_components	*previous;

	temp = *head;
	while (--n)
	{
		previous = temp;
		temp = temp->next;
	}
	previous->next = temp->next;
	free(temp->token);
	free(temp->type.type);
	free(temp);
}

int	has_command(t_components **tokens)
{
	t_components	*check_command;

	check_command = *tokens;
	while (check_command != NULL && ft_strcmp(check_command->type.type, "PIPE"))
	{
		if (!ft_strcmp(check_command->type.type, "COMMAND"))
			return (1);
		check_command = check_command->next;
	}
	return (0);
}

void	insert_command_at_front(t_components **tokens)
{
	t_components	*goal;
	char			*type;
	char			*token;
	t_components	*temp;
	int				position;

	temp = NULL;
	if (!has_command(tokens))
		return ;
	if (*tokens == NULL)
		return ;
	goal = *tokens;
	position = 0;
	while (goal != NULL && strcmp(goal->type.type, "COMMAND") != 0)
	{
		goal = goal->next;
		position++;
	}
	token = ft_strdup(goal->token);
	type = ft_strdup(goal->type.type);
	deleteposition(tokens, position + 1);
	addnodetofront(tokens, token, type);
}

void	update(t_components *pipe_node,
			t_components *red_node)
{
	t_components	*tempp;
	t_components	*tempp2;
	t_components	*tempp10;
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	tempp = red_node;
	flag = 0;
	tempp10 = red_node;
	if (!has_command(&tempp10))
		return ;
	while (tempp != NULL && tempp->next != NULL
		&& ft_strcmp(tempp->next->type.type, "COMMAND"))
		tempp = tempp->next;
	tempp2 = tempp->next;
	if (tempp->next->next)
		tempp->next = tempp2->next;
	else
		tempp->next = NULL;
	pipe_node->next = tempp2;
	tempp2->next = red_node;
}

t_components	*insert_at_position(t_components *node)
{
	t_components	*temp;

	temp = node;
	while (temp)
	{
		if (temp->next == NULL)
			break ;
		if (!ft_strcmp(temp->type.type, "PIPE")
			&& check_is_redirection(temp->next->token))
			update(temp, temp->next);
		temp = temp->next;
	}
	return (node);
}
