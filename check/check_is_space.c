/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:51:25 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 01:02:11 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countspaces(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			while (input[i] != '\0' && (input[i] != '\'' || input[i] != '\"'))
				i++;
		}
		if (includes(input[i]) && input[i + 1] != '>' && input[i + 1] != '<')
		{
			if (input[i + 1] == ' ' && input[i - 1] != ' ')
				count += 1;
			if (input[i + 1] != ' ' && input[i - 1] == ' ')
				count += 1;
			if (input[i + 1] != ' ' && input[i - 1] != ' ')
				count += 2;
		}
		i++;
	}
	return (count);
}

int	countdoublegreaterthan(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == '>' && input[i + 1] == '>'))
		{
			if (input[i - 1] != ' ' && input[i + 2] == ' ' && i != 0)
				count += 1;
			else if (input[i - 1] == ' ' && input[i + 2] != ' ' && i != 0)
				count += 1;
			else if (input[i - 1] != ' ' && input[i + 2] != ' ' && i != 0)
				count += 2;
			if (i == 0 && input[i] == '>' && input[i + 1] == '>' && input[i
					+ 2] != ' ')
				count++;
			i += 1;
		}
		i++;
	}
	return (count);
}

int	countdoublelessthan(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == '<' && input[i + 1] == '<'))
		{
			if (input[i - 1] != ' ' && input[i + 2] == ' ' && i != 0)
				count += 1;
			else if (input[i - 1] == ' ' && input[i + 2] != ' ' && i != 0)
				count += 1;
			else if (input[i - 1] != ' ' && input[i + 2] != ' ' && i != 0)
				count += 2;
			if (i == 0 && input[i] == '<' && input[i + 1] == '<' && input[i
					+ 2] != ' ')
				count++;
			i += 1;
		}
		i++;
	}
	return (count);
}

int	check_is_space(char *input)
{
	int	count;

	count = 0;
	count += countspaces(input);
	count += countdoublegreaterthan(input);
	count += countdoublelessthan(input);
	return (count);
}
