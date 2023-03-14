/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/03/14 00:20:51 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display(t_tokens *token)
{
	t_tokens	*node;

	node = token;
	while (node != NULL)
	{
		printf("%s ", node->token);
		node = node->next;
	}
	write(1,"\n",1);
}

int	main(int argc, char **argv, char **envp)
{
	
	char		*username;
	t_tokens	*head;
	char		*input;

	head = NULL;
	username = ft_strjoin(getenv("USER"), "@:");
	char *full_username;
	full_username = ft_strjoin(username,"user > ");
	if (username == NULL)
	{
		write(2, "Could not get username", ft_strlen("Could not get username"));
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline(full_username);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (strlen(input) == 0)
			continue ;
		add_history(input);
		parse(input, &head,envp);
		free(input);
		input = NULL;
		while (head)
		{
			free(head->token);
			head->token = NULL;
			head = head->next;
		}
		free(head);
	}
	free(username);
	username = NULL;
}
