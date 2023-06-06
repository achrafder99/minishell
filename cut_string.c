/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 04:59:19 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 20:09:32 by adardour         ###   ########.fr       */
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
		if ((s[i] == '\'' || s[i] == '\"') && s[i])
		{
			qoute = s[i];
			count += 1;
			i++;
			while (s[i] != qoute && s[i] != '\0')
				i++;
			if (s[i] == qoute)
				count++;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (count);
}

char	*cut_string(char *s)
{
	int		i;
	int		j;
	char	qoute;
	char	*s1;

	i = 0;
	j = 0;
	s1 = malloc(sizeof(char) * ((ft_strlen(s) - count_quotes(s)) + 1));
	if (!s1)
		return (0);
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			qoute = s[i++];
			while (qoute != s[i] && s[i] != '\0')
				s1[j++] = s[i++];
			i++;
		}
		if (s[i] == '\0')
			break ;
		s1[j++] = s[i++];
	}
	s1[j] = '\0';
	return (s1);
}
