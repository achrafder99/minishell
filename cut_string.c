/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 04:59:19 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 15:54:50 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_quotes(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*cut_string(char *s)
{
	int		i;
	char 	*qoute;
	int		j;
	int		size;
	char	*s1;

	i = 0;
	j = 0;
	size = ft_strlen(s) - count_quotes(s);
	s1 = malloc(sizeof(char) * (size + 1));
	if (!s1)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			qoute = s[i];
			while (s[i] != qoute && s[i] != '\0')
			{
				s1[j] = s[i];
				i++;
			}
		}
		s1[j] = s[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}
