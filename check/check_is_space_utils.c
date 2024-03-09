/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_space_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:30:11 by aalami            #+#    #+#             */
/*   Updated: 2023/06/07 14:45:09 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_qouted(char *input, int *i)
{
	int	qoute;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		qoute = input[*i];
		(*i)++;
		while (input[*i] != qoute && input[*i] != '\0')
			(*i)++;
	}
}

void	count_double_greater_util(char *input, int *i, int *count)
{
	if ((input[*i] == '>' && input[*i + 1] == '>'))
	{
		if (input[*i - 1] != ' ' && input[*i + 2] == ' ' && *i != 0 && input[*i \
			+ 2] != '\0')
			(*count) += 1;
		else if (input[*i - 1] == ' ' && input[*i + 2] != ' ' && *i != 0
			&& input[*i + 2] != '\0')
			(*count) += 1;
		else if (input[*i - 1] != ' ' && input[*i + 2] != ' ' && *i != 0
			&& input[*i + 2] != '\0')
			(*count) += 2;
		if (i == 0 && input[*i] == '>' && input[*i + 1] == '>' && input[*i \
			+ 2] != ' ')
			(*count)++;
		*i += 1;
	}
}

void	count_double_less_util(char *input, int *i, int *count)
{
	if ((input[*i] == '<' && input[*i + 1] == '<'))
	{
		if (input[*i - 1] != ' ' && input[*i + 2] == ' ' && *i != 0 && input[*i \
			+ 2] != '\0')
			(*count) += 1;
		else if (input[*i - 1] == ' ' && input[*i + 2] != ' ' && *i != 0
			&& input[*i + 2] != '\0')
			(*count) += 1;
		else if (input[*i - 1] != ' ' && input[*i + 2] != ' ' && *i != 0
			&& input[*i + 2] != '\0')
			(*count) += 2;
		if (i == 0 && input[*i] == '<' && input[*i + 1] == '<' && input[*i \
			+ 2] != ' ')
			(*count)++;
		*i += 1;
	}
}
