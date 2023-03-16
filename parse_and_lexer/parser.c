/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:52:46 by adardour          #+#    #+#             */
/*   Updated: 2023/03/16 21:59:17 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_is_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

void	parser(t_tokens *head)
{
	char	*command;
	char	*err;
		t_tokens *token;

	if (check_is_built_in(head->token))
	{
		if (!ft_strcmp(head->token, "cd"))
			cd(head);
		else if (!ft_strcmp(head->token, "pwd"))
			pwd(head);
		else if (!ft_strcmp(head->token, "echo"))
			echo(head);
		return ;
	}
	command = ft_strjoin("/bin/", head->token);
	if (access(command, X_OK) == 0)
	{
		token = head;
		while (token != NULL)
		{
			printf("Token (%s)  Type (%s) \n", token->token, token->type.type);
			token = token->next;
		}
	}
	else
	{
		err = "command not found: ";
		write(2, err, ft_strlen(err));
		write(2, head->token, ft_strlen(head->token));
		write(2, "\n", 1);
	}
}
