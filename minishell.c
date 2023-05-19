/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/05/18 23:06:24 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_handler(int signal)
{
	if (signal == 3)
		printf("");
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*display_name(void)
{
	char	*username;
	char	*display;

	username = getenv("USER");
	if (username == NULL)
	{
		write(2, "Could not get username", strlen("Could not get username"));
		return (NULL);
	}
	display = ft_strjoin(username, "@:> ");
	return (display);
	free(display);
}

char	*get_input(void)
{
	char	*full_username;
	char	*input;

	full_username = display_name();
	if (full_username == NULL)
	{
		return (NULL);
	}
	input = readline(full_username);
	free(full_username);
	return (input);
}

void	process_input(char *input, t_env *env, t_info *info)
{
	t_components	*head;

	if (input == NULL)
	{
		write(1, " exit\n", 6);
		exit(0);
	}
	if (strlen(input) == 0)
	{
		return ;
	}
	add_history(input);
	head = NULL;
	lexer(input, &head, info, env);
}
