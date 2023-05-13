/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:58:39 by adardour          #+#    #+#             */
/*   Updated: 2023/05/05 19:02:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*buffer;
	char		*start;
	char		*end;
	char		*start;
	char		*end;
	char		*qstart;
	char		*qend;

	buffer = NULL;
	if (str != NULL)
		buffer = str;
	if (buffer == NULL || *buffer == '\0')
		return (NULL);
	while (*buffer != '\0' && strchr(delim, *buffer) != NULL)
		buffer++;
	if (*buffer == '\"')
	{
		start = buffer + 1;
		end = strchr(start, '\"');
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
		if (*end == '\"')
		{
			qstart = end + 1;
			qend = strchr(qstart, '\"');
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
	char	*token;
	int		count;

	count = 0;
	token = ft_strtok(string, " ");
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, " ");
	}
	return (count);
}
