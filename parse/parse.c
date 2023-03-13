/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/03/14 00:19:54 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_things(char **commands, t_tokens **head)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
	{
		push(head, commands[i]);
		i++;
	}
}

int	is_built_in(char *first_node)
{
	if (!ft_strcmp(first_node, "echo"))
		return (1);
	else if (!ft_strcmp(first_node, "cd"))
		return (1);
	else if (!ft_strcmp(first_node, "pwd"))
		return (1);
	else if (!ft_strcmp(first_node, "export"))
		return (1);
	else if (!ft_strcmp(first_node, "unset"))
		return (1);
	else if (!ft_strcmp(first_node, "env"))
		return (1);
	else if (!ft_strcmp(first_node, "exit"))
		return (1);
	return (0);
}

void	execute_built_in(t_tokens *tokens, char **env)
{
	if (!ft_strcmp(tokens->token, "echo"))
		echo(tokens, env);
	else if (!ft_strcmp(tokens->token, "cd"))
		cd(tokens);
	else if (!ft_strcmp(tokens->token, "pwd"))
		pwd(tokens);
	else if (!ft_strcmp(tokens->token, "exit"))
		exit_shell();
}

void	parse(char *input, t_tokens **head, char **env)
{
	char	**commands;
	int		i;

	commands = ft_split(input, ' ');
	push_things(commands, head);
	if (is_built_in((*head)->token))
		execute_built_in(*head, env);
}
