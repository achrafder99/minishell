/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:51:25 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 14:40:22 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_next_prev(char *input, int i)
{
	return (input[i + 1] != '>' && input[i + 1] != '<' && input[i - 1] != '>'
		&& input[i - 1] != '<');
}

int	countspaces(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			while (input[i++] != '\0' && input[i] != '\"' && input[i] != '\'')
				i++;
		}
		if (includes(input[i]) && check_next_prev(input, i))
		{
			if (input[i + 1] == ' ' && input[i - 1] != ' ' && i > 0)
				count += 1;
			else if (input[i + 1] != ' ' && input[i - 1] == ' ' && i > 0)
				count += 1;
			else if (input[i + 1] != ' ' && input[i - 1] != ' ' && i > 0)
				count += 2;
			else if (i == 0 && input[i + 1] != ' ')
				count++;
		}
	}
	return (count);
}

int	countdoublegreaterthan(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		ignore_qouted(input, &i);
		count_double_greater_util(input, &i, &count);
	}
	return (count);
}

int	countdoublelessthan(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		ignore_qouted(input, &i);
		count_double_less_util(input, &i, &count);
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
