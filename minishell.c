/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 22:47:05 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_name(void)
{
	char	*username;
	char	*full_username;
	char	*temp;
	char	*dd;

	username = ft_strjoin(getenv("USER"), "@:");
	temp = username;
	free(username);
	if (temp == NULL)
	{
		write(2, "Could not get username", ft_strlen("Could not get username"));
		exit(EXIT_FAILURE);
	}
	dd = ft_strjoin(temp, " > ");
	return (dd);
}

char	*lowercase(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] >= 65 && input[i] <= 90)
			input[i] = input[i] + 32;
		i++;
	}
	return (input);
}

char	*get_input(void)
{
	char	*input;
	char	*full_username;
	char	*tt;

	input = NULL;
	full_username = display_name();
	tt = ft_strjoin(full_username, "");
	free(full_username);
	full_username = NULL;
	input = readline(tt);
	free(tt);
	return (input);
}

void	process_input(char *input, t_info *info)
{
	t_components	*head;

	if (input == NULL)
	{
		write(1, " ", 1);
		write(1, "exit\n", 5);
		exit(1);
	}
	else if (strlen(input) == 0)
	{
		free(input);
		input = NULL;
		return ;
	}
	head = NULL;
	add_history(input);
	lexer(input, &head, info);
	free(input);
	input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*input;

	signal(SIGINT, handle_signals);
	while (1)
	{
		input = get_input();
		process_input(input, &info);
	}
	return (0);
}
