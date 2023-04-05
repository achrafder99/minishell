/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 03:49:25 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	add_space_after1(char *new_str, int *i, int *j)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = '>';
	new_str[(*j)++] = '>';
	new_str[(*j)++] = ' ';
	(*i)++;
}

void	add_space_after2(char *new_str, int *i, int *j)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = '<';
	new_str[(*j)++] = '<';
	new_str[(*j)++] = ' ';
	(*i)++;
}

void	add_space_after3(char *new_str, int i, int *j, char *str)
{
	new_str[(*j)++] = ' ';
	new_str[(*j)++] = str[i];
	new_str[(*j)++] = ' ';
}

char	*new_str(char *str, int count)
{
	int		i;
	int		j;
	int		length;
	char	*new_str;

	i = -1;
	j = 0;
	length = ft_strlen(str) + count * 2;
	new_str = (char *)malloc(length + 1);
	while (i++ < length - 1)
	{
		if (str[i] == '>' && str[i + 1] == '>')
			add_space_after1(new_str, &i, &j);
		else if (str[i] == '<' && str[i + 1] == '<')
			add_space_after2(new_str, &i, &j);
		else
		{
			if (includes(str[i]))
				add_space_after3(new_str, i, &j, str);
			else
				new_str[j++] = str[i];
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
