/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/29 23:59:50 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	add_before_and_after(char *restring, char *str, int i, int *j)
{
	restring[(*j)++] = ' ';
	restring[(*j)++] = str[i];
	restring[(*j)++] = str[i + 1];
	restring[(*j)++] = ' ';
}

char	*allocation(char *str, int count)
{
	char	*restring;

	restring = malloc(sizeof(char) * (ft_strlen(str) + count + 1));
	if (!restring)
	{
		perror("");
		exit(1);
	}
	return (restring);
}

char	*handleincludes(char *str, int i, char *restring, int *j)
{
	if (i > 0 && str[i - 1] != ' ')
		restring[(*j)++] = ' ';
	restring[(*j)++] = str[i];
	if ((size_t)i < ft_strlen(str) - 1 && str[i + 1] != ' ')
		restring[(*j)++] = ' ';
	return (restring);
}

char	*handledoublearrow(char *str, int i, char *restring, int *j)
{
	if (i > 0 && str[i - 1] != ' ' && str[i + 2] != ' ')
		add_before_and_after(restring, str, i, j);
	else if (i > 0 && str[i - 1] != ' ' && str[i + 2] == ' ')
	{
		restring[(*j)++] = ' ';
		restring[(*j)++] = str[i++];
		restring[(*j)++] = str[i++];
		restring[(*j)++] = ' ';
	}
	else if (i > 0 && str[i - 1] == ' ' && str[i + 2] != ' ')
	{
		restring[(*j)++] = str[i++];
		restring[(*j)++] = str[i++];
		restring[(*j)++] = ' ';
	}
	else
	{
		restring[(*j)++] = str[i++];
		restring[(*j)++] = str[i++];
		restring[(*j)++] = ' ';
		restring[*j] = str[i++];
	}
	return (restring);
}

char	*new_str(char *str, int count)
{
	char	*restring;
	int		j;
	int		i;

	j = 0;
	i = 0;
	restring = allocation(str, count);
	while ((size_t)i < (ft_strlen(str) + count))
	{
		if (includes(str[i]) && str[i + 1] != '>' && str[i + 1] != '<')
		{
			restring = handleincludes(str, i, restring, &j);
			i++;
		}
		else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
		{
			restring = handledoublearrow(str, i, restring, &j);
			i += 2;
			if (str[i] == ' ')
				i += 1;
		}
		else
			restring[j++] = str[i++];
	}
	restring[j] = '\0';
	return (restring);
}
