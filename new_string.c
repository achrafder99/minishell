/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 13:58:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*new_str(char *str, int count)
{
	char *restring;
	restring = malloc(sizeof(char) * strlen(str) + count + 1);
	if (!restring)
	{
		perror("");
		exit(1);
	}
	int j = 0;

	int i = 0;
	while (i < strlen(str))
	{
		if (includes(str[i]) && (str[i + 1] != '>' && str[i + 1] != '<'))
		{
			if (i > 0 && str[i - 1] != ' ')
				restring[j++] = ' ';
			restring[j++] = str[i++];
			if (i < strlen(str) - 1 && str[i + 1] != ' ')
				restring[j++] = ' ';
		}
		else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
		{
			if (str[i + 1] == '>' && str[i] == '>')
			{
				if (i > 0 && str[i - 1] != ' ' && str[i + 2] != ' ')
				{
					restring[j++] = ' ';
					restring[j++] = str[i];
					i++;
					restring[j++] = str[i];
					i++;
					restring[j++] = ' ';
				}
				else if (i > 0 && str[i - 1] != ' ' && str[i + 2] == ' ')
				{
					restring[j++] = ' ';
					restring[j++] = str[i];
					i++;
					restring[j++] = str[i];
					i++;
					restring[j++] = ' ';
				}
				else if (i > 0 && str[i - 1] == ' ' && str[i + 2] != ' ')
				{
					restring[j++] = str[i++];
					restring[j++] = str[i++];
					restring[j++] = ' ';
				}
				else
				{
					restring[j++] = str[i++];
					restring[j++] = str[i++];
					restring[j] = ' ';
				}
			}
			else
			{
				if (i > 0 && str[i - 1] != ' ' && str[i + 2] != ' ')
				{
					restring[j++] = ' ';
					restring[j++] = str[i];
					i++;
					restring[j++] = str[i];
					i++;
					restring[j++] = ' ';
				}
				else if (i > 0 && str[i - 1] != ' ' && str[i + 2] == ' ')
				{
					restring[j++] = ' ';
					restring[j++] = str[i];
					i++;
					restring[j++] = str[i];
					i++;
					restring[j++] = ' ';
				}
				else if (i > 0 && str[i - 1] == ' ' && str[i + 2] != ' ')
				{
					restring[j++] = str[i++];
					restring[j++] = str[i++];
					restring[j++] = ' ';
				}
				else
				{
					restring[j++] = str[i++];
					restring[j++] = str[i++];
					restring[j] = ' ';
				}
			}
		}
		else
			restring[j++] = str[i++];
	}
	restring[j] = '\0';
	return (restring);
}
