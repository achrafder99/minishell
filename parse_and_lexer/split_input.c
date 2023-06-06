/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 19:50:42 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_token(char *str, int del)
{
	char	**tokens;
	int		number_of_token;
	int		i;

	i = 0;
	number_of_token = count_token(str, del);
	tokens = allocate_tokens(str, del);
	while (*str != '\0' && i < number_of_token)
	{
		while (*str == del && *str != '\0')
			str++;
		if (*str != del && *str != '\0')
		{
			tokens[i] = malloc(sizeof(char) * count_length_token(str) + 1);
			if (!tokens[i])
			{
				perror("");
				exit(1);
			}
			fill(&str, i, tokens);
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

void	check_qoutaions(char *str, int *i, int del)
{
	char	qoute;

	while (str[(*i)] != del && str[(*i)] != '\0')
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
		{
			qoute = str[(*i)];
			(*i)++;
			while (str[(*i)] != qoute)
				(*i)++;
			if ((str[(*i + 1)] == del || (str[(*i + 1)] == '\'' || \
			str[(*i +1)] == '\"')))
			{
				(*i)++;
				break ;
			}
		}
		(*i)++;
	}
}

int	count_token(char *str, int del)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != del)
		{
			count++;
			check_qoutaions(str, &i, del);
		}
		while (str[i] == del && str[i] != '\0')
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
		splitting = split_token(str, ' ');
	else
		splitting = split_token(input, ' ');
	if (str)
		free(str);
	return (splitting);
}
