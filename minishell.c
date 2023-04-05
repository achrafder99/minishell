/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 18:18:53 by aalami           ###   ########.fr       */
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

void	process_input(char *input, t_info *info, t_lst *env, t_lst *exp)
{
	t_components	*head;

	if (input == NULL)
	{
		write(1, " ", 1);
		write(1, "exit\n", 5);
		exit(1);
	}
	else if (strlen(input) == 0)
		return ;
	head = NULL;
	add_history(input);
	lexer(input, &head, info, env, exp);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*input;
	t_lst	*env;
	t_lst	*exp;

	env = get_env(envp);
	exp = get_export_env(envp);
	signal(SIGINT, handle_signals);
	while (1)
	{
		input = get_input();
		process_input(input, &info, env, exp);
		free(input);
		input = NULL;
	}
	return (0);
}
