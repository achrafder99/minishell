/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:17:54 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 16:37:18 by adardour         ###   ########.fr       */
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

char	**allocate_tokens(char *str, int del)
{
	char	**tokens;

	tokens = (char **)malloc(sizeof(char *) * count_token(str, del) + 1);
	if (!tokens)
	{
		perror("");
		exit(1);
	}
	return (tokens);
}

int	count_quote_length(char *str)
{
	int		allocations;
	char	quote;

	allocations = 1;
	quote = *str;
	str++;
	while (*str != quote && *str != '\0')
	{
		allocations++;
		str++;
	}
	if (*str != '\0' && (*str == quote || (*str == ' ' && (*(str + 1) != '\''
					|| *(str + 1) == '\"'))))
		allocations++;
	return (allocations);
}

int	count_length_token(char *str)
{
	int		allocations;
	char	*temp;

	allocations = 0;
	temp = str;
	while (*temp != ' ' && *temp != '\0')
	{
		if (*temp == '\0')
			break ;
		if ((*temp == '\'' || *temp == '\"') && *temp != '\0')
		{
			allocations += count_quote_length(temp);
			temp += count_quote_length(temp);
		}
		else
		{
			allocations++;
			temp++;
		}
	}
	return (allocations);
}

int	proccess_qouted(char *str, char **tokens, int *i, int *j)
{
	if (*str + 1 == ' ' || *str + 1 == '\'' || *str + 1 == '\"')
	{
		tokens[*i][(*j)++] = *str;
		(*str)++;
		return (1);
	}
	else
		tokens[*i][(*j)++] = *str;
	return (0);
}

void	fill(char **str, int i, char **tokens)
{
	int		j;
	char	quote;

	j = 0;
	while (**str != ' ' && **str != '\0')
	{
		tokens[i][j++] = **str;
		if (**str == '\'' || **str == '\"')
		{
			quote = **str;
			(*str)++;
			while (**str != quote && **str != '\0')
			{
				tokens[i][j++] = **str;
				(*str)++;
			}
			if (proccess_qouted(*str, tokens, &i, &j))
				break ;
		}
		(*str)++;
	}
	tokens[i][j] = '\0';
}
