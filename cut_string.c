/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 04:59:19 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 17:29:04 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_quotes(char *s)
{
	int		count;
	char	qoute;
	int		i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			count += 1;
			qoute = s[i];
			i++;
			while (s[i] != qoute && s[i] != '\0')
				i++;
			if (s[i] == qoute)
			{
				count++;
			}
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (count);
}

char	*cut_string(char *s)
{
	int i;
	int j;
	char qoute;

	i = 0;
	j = 0;
	int size = ft_strlen(s) - 2;
	char *s1 = malloc(sizeof(char) * (size + 1));
	if (!s1)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qoute = s[i];
			i++;
			while (qoute != s[i] && s[i] != '\0')
			{
				s1[j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		s1[j] = s[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}
