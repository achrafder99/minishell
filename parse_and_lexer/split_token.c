/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:17:54 by adardour          #+#    #+#             */
/*   Updated: 2023/05/20 16:53:51 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/05/08 18:32:28 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_tokens(char *str)
{
	char	**tokens;

	tokens = malloc(sizeof(char **) * count_token(str) + 1);
	if (!tokens)
	{
		perror("");
		exit(1);
	}
	return (tokens);
}

int	count_length_token(char *str)
{
	int		allocations;
	char	*temp;
	char	qoute;

	allocations = 0;
	temp = str;
	while (*temp != ' ' && *temp != '\0')
	{
		allocations++;
		if (*temp == '\'' || (*temp == '\"' && *temp != '\0'))
		{
			qoute = *temp;
			temp++;
			allocations += 1;
			while (*temp != qoute && *temp != '\0')
			{
				allocations++;
				temp++;
			}
		}
		temp++;
	}
	return (allocations);
}

void	fill(char **str, int i, char **tokens)
{
	int		j;
	char	qoute;

	j = 0;
	while (**str != ' ' && **str != '\0')
	{
		tokens[i][j++] = **str;
		if (**str == '\'' || **str == '\"')
		{
			qoute = **str;
			(*str)++;
			while (**str != qoute)
			{
				tokens[i][j++] = **str;
				(*str)++;
			}
			if (**str == qoute)
				tokens[i][j++] = **str;
		}
		(*str)++;
	}
	tokens[i][j] = '\0';
}

char	**split_token(char *str)
{
	char	**tokens;
	int		number_of_token;
	int		i;

	i = 0;
	number_of_token = count_token(str);
	tokens = allocate_tokens(str);
	while (*str != '\0' && i < number_of_token)
	{
		if (*str != ' ')
		{
			tokens[i] = malloc(sizeof(char) * count_length_token(str) + 1);
			if (!tokens[i])
			{
				perror("");
				exit(1);
			}
			fill(&str, i, tokens);
		}
		while (*str == ' ' && *str != '\0')
			str++;
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
