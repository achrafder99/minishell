/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/03/16 19:58:21 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*username;
	t_tokens	*head;
	char		*input;
	char		*full_username;

	head = NULL;
	username = ft_strjoin(getenv("USER"), "@:");
	full_username = ft_strjoin(username, "user > ");
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
		lexer(input, &head);

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
