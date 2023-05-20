/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 16:28:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_qoutaions(char *str, int *i)
{
	char	qoute;

	while (str[(*i)] != ' ' && str[(*i)] != '\0')
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
		{
			qoute = str[(*i)];
			(*i)++;
			while (str[(*i)] != qoute)
				(*i)++;
			if (str[(*i)] == qoute)
			{
				(*i)++;
				return ;
			}
		}
		(*i)++;
	}
}

int	count_token(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			check_qoutaions(str, &i);
		}
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	return (count);
}

char	**split_input(char *input)
{
	char	*str;
	char	**splitting;

	str = NULL;
	splitting = NULL;
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		splitting = split_token(str);
	else
		splitting = split_token(input);
	if (str)
		free(str);
	return (splitting);
}
