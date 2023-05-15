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

int	count_token(char *str)
{
	int i;
	int count;
	int flag;
	char qoute;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			while (str[i] != ' ' && str[i] != '\0')
			{
				if (str[i] == '\'' || str[i] == '\"')
				{
					qoute = str[i];
					i++;
					while (str[i] != qoute)
                        i++;
				}
				i++;
			}
		}
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	return (count);
}

char **split_token(char *str)
{
    char **tokens;
    int    i;
    int    j;
    int    allocations;
    char qoute;
    char *temp;


    int    number_of_tokens = count_token(str);
    i = 0;
    allocations = 0;

    tokens = malloc(sizeof(char **) * number_of_tokens + 1);
    if (!tokens)
    {
        perror("");
        exit(1);
    }
    while (*str != '\0' && i < number_of_tokens)
    {
        if (*str != ' ')
        {
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
            tokens[i] = malloc(sizeof(char) * allocations + 1);
            allocations = 0;
            if (!tokens[i])
            {
                perror("");
                exit(1);
            }
            j = 0;
            while (*str != ' ' && *str != '\0')
            {
                tokens[i][j] = *str;
                j++;
                if (*str == '\'' || *str == '\"')
                {
                    qoute = *str;
                    str++;
                    while (*str != qoute)
                    {
                        tokens[i][j] = *str;
                        j++;
                        str++;
                    }
                    if (*str == qoute)
                    {
                      tokens[i][j] = qoute;
                      j++;
                    }
                }
                str++;
            }
            tokens[i][j] = '\0';
        }
        while (*str == ' ' && *str != '\0')
            str++;
		i++;
    }
	tokens[i] = NULL;
    return(tokens);
}

char	**split_input(char *input)
{
	char	*str;
	char	*error;
	char	**spliting;
	int		i;

	i = 0;
	str = NULL;
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		spliting = split_token(str);
	else
		spliting = split_token(input);
	if (str)
		free(str);
	return (spliting);
}
