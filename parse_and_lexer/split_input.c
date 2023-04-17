/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/04/17 04:00:40 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char* strtok_quoted(char* str, const char* delim)
{
    static char* buffer = NULL;
    if (str != NULL)
        buffer = str;
    if (buffer == NULL || *buffer == '\0')
        return NULL;
    while (*buffer != '\0' && strchr(delim, *buffer) != NULL)
        buffer++;
    if (*buffer == '\"')
	{
        char* start = buffer + 1;
        char* end = strchr(start, '\"');
		end++;
        if (end == NULL)
            return NULL;
        *end = '\0';
        buffer = end + 1;
        return (start - 1);
    }
    char* start = buffer;
    char* end = buffer;
    while (*end != '\0' && strchr(delim, *end) == NULL)
	{
        if (*end == '\"') {
            char* qstart = end + 1;
            char* qend = strchr(qstart, '\"');
            if (qend == NULL)
                return (NULL);
            end = qend;
        }
        end++;
    }
    if (end == start)
	{
        buffer = NULL;
        return NULL;
    }
    if (*end == '\"')
        end++;
    if (*end != '\0')
	{
        *end = '\0';
        buffer = end + 1;
    }
	else
        buffer = NULL;
    return (start);
}

int	number_of_token(char *string)
{
	char *token;
	int count;

	count = 0;
	token = strtok_quoted(string, " ");
    while (token != NULL)
    {
        count++;
        token = strtok_quoted(NULL, " ");
    }
	return (count);
}

char **split_2(char *input)
{
    char *string;
    int count;
    char **result;
	char *token;
	int i;
	
	string = ft_strdup(input);
    result = (char **)malloc(sizeof(char *) * (number_of_token(input) + 1));
    if (!result)
    {
        perror("");
        exit(1);
    }
	i = 0;
	token = strtok_quoted(string, " ");
    while (token != NULL)
    {
		result[i] = ft_strdup(token);
        i++;
        token = strtok_quoted(NULL, " ");
    }
    result[i] = NULL;
    return (result);
}

char	**split_input(char *input)
{
	char	*str;
	char	*error;
	char	**spliting;
	int		i;

	i = 0;
	str = NULL;
	if (!check_quotes(input))
	{
		error = "Syntax Error: String must be closed\n";
		write(2, error, ft_strlen(error));
		return (NULL);
	}
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		spliting = split_2(str);
	else
		spliting = split_2(input);
	free(str);
	return (spliting);
}
