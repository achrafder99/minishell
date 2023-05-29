/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:59:10 by aalami            #+#    #+#             */
/*   Updated: 2023/05/29 23:37:49 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt_handler(int signal)
{
	if (signal == 3)
		printf("");
	else if (signal == 2 && !g_heredoc_flag)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		g_heredoc_flag = -1;
		close(STDIN_FILENO);
	}
}

char	*display_name(void)
{
	char	*username;
	char	*display;

	username = getenv("USER");
	if (username == NULL)
	{
		username = ft_strdup("minishell");
		display = ft_strjoin(username, "@:> ");
		free(username);
	}
	else
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
		return ;
	}
	if (ft_strlen(input) == 0)
		return ;
	add_history(input);
	head = NULL;
	lexer(input, &head, info, env);
}
