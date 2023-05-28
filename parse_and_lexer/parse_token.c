/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:29:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/26 18:58:38 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_components	*insert_command_at_front(t_components *tokens)
{
	t_components	*goal;
	t_components	*temp;
	t_components	*check_command;
	int				flag;

	flag = 0;
	temp = NULL;
	check_command = tokens;
	if (!has_command(&check_command))
		return (tokens);
	if (tokens == NULL)
	{
		tokens = temp;
		return (NULL);
	}
	goal = tokens;
	while (goal != NULL && ft_strcmp(goal->type.type, "COMMAND") != 0)
		goal = goal->next;
	if (goal != NULL)
	{
		temp = goal;
		tokens = delete_node_by_type(&tokens, "COMMAND");
		ft_lstadd_front(&tokens, temp);
	}
	return (tokens);
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
