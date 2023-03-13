/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/03/13 23:49:55 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_length(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_echo(char *string, char **env)
{
	char	**spliting;
	int		i;
	char	*value;

	if (ft_strchr(string, '$'))
	{
		while (*string != '$')
		{
			write(1, string, 1);
			string++;
		}
		spliting = ft_split(string, '$');
		i = 0;
		while (spliting[i] != NULL)
		{
			value = getenv(spliting[i]);
			if (value == NULL)
				write(1, "", 1);
			else
				write(1, value, ft_strlen(value));
			i++;
		}
	}
	else
		write(1, string, ft_strlen(string));
}

void	echo(t_tokens *tokens, char **env)
{
	t_tokens *echo_command;
	echo_command = tokens->next;
	int flags;
	flags = 0;
	if (tokens->next == NULL )
		return;
	if (!ft_strcmp(echo_command->token, "-n"))
	{
		flags = 1;
		while (!ft_strcmp(echo_command->token, "-n"))
			echo_command = echo_command->next;
	}
	while (echo_command != NULL)
	{
		ft_echo(echo_command->token, env);
		echo_command = echo_command->next;
		write(1, " ", 1);
	}
	if (!flags)
		write(1, "\n", 1);
}