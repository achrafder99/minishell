/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/03/16 21:49:40 by adardour         ###   ########.fr       */
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

int	is_special_caractere(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			return (1);
		}
		if (string[i] == '\\')
		{
			if (string[i] == '\n')
				return (1);
			if (string[i] == '\r')
				return (1);
			if (string[i] == '\t')
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_put_special(char *string)
{
	int		i;
	char	**spliting;
	char	*value;

	i = 0;
	if (ft_strchr(string, '$'))
	{
		while (*string != '$')
		{
			write(1, string, 1);
			string++;
		}
		spliting = ft_split(string, '$');
		while (*spliting != NULL)
		{
			value = getenv(*spliting);
			if (!value)
				write(1, "", 1);
			else
				write(1, value, ft_strlen(value));
			spliting++;
		}
	}
}

void	echo(t_tokens *tokens)
{
	t_tokens *echo_command;
	echo_command = tokens->next;

	int flags;
	flags = 0;
	while (echo_command != NULL)
	{
		if (ft_strcmp(echo_command->token, "-n"))
			break ;
		flags = 1;
		echo_command = echo_command->next;
	}
	while (echo_command != NULL)
	{
		if (is_special_caractere(echo_command->token))
			ft_put_special(echo_command->token);
		else
			write(1, echo_command->token, ft_strlen(echo_command->token));
		write(1, " ", 1);
		echo_command = echo_command->next;
	}
	if (!flags)
		write(1, "\n", 1);
}