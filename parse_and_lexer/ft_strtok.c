/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:58:39 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 13:59:57 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*buffer;
	char		qoute;
	char		*qend;
	char		*start;
	char		*end;
	char		*start;
	char		*end;
	char		*qstart;

	buffer = NULL;
	if (str != NULL)
		buffer = str;
	if (buffer == NULL || *buffer == '\0')
		return (NULL);
	while (*buffer != '\0' && ft_strchr(delim, *buffer) != NULL)
		buffer++;
	if (*buffer == '\"' || *buffer == '\'')
	{
		qoute = *buffer;
		start = buffer + 1;
		end = strchr(start, qoute);
		end++;
		if (end == NULL)
			return (NULL);
		*end = '\0';
		buffer = end + 1;
		return (start - 1);
	}
	start = buffer;
	end = buffer;
	while (*end != '\0' && strchr(delim, *end) == NULL)
	{
		if (*end == '\"' || *end == '\'')
		{
			qstart = end + 1;
			if (ft_strchr(qstart, '\"'))
				qend = ft_strchr(qstart, '\"');
			else
				qend = ft_strchr(qstart, '\'');
			if (qend == NULL)
				return (NULL);
			end = qend;
		}
		end++;
	}
	if (end == start)
	{
		buffer = NULL;
		return (NULL);
	}
	if (*end == '\"' || *end == '\'')
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
	int count = 0;
	token = ft_strtok(string, " ");
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, " ");
	}
	return (count);
}