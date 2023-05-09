/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:34:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/07 21:10:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    number(char *string)
{
    int i;
    int flag_space;
    int count;
	
    i = 0;
    count = 0;
    flag_space = 0;
    while (string[i] != '\0')
    {
        if(string[i] == '\'' || string[i] == '\"')
        {
            while (string[i] != '\0' && (string[i] != '\'' || string[i] != '\"'))
            {
                count++;
                i++;
            }
        }
        while (string[i] != '\0' && string[i] != ' ')
        {
            count++;
            i++;
			if (string[i] == ' ')
			{
				count++;
				flag_space = !flag_space;
				break;
			}
        }
        if(string[i] == ' ' && !flag_space)
		{
            flag_space = !flag_space;
            count += 1;
        }
        if(string[i] == '\0')
            break;
        i++;
    }
    return (count);
}

char *restring(char *input, int allocation)
{
	int i;
	int j;
	int flag_space;
	char *restring;

	i = 0;
	j = 0;
	flag_space = 0;
	restring = malloc(sizeof(char)* allocation + 1);
	while (input[i] != '\0')
	{
		if(input[i] == '\'' || input[i] == '\"')
        {
            while (input[i] != '\0' && (input[i] != '\'' || input[i] != '\"'))
            {
                restring[j++] = input[i];
                i++;
            }
        }
        while (input[i] != '\0' && input[i] != ' ')
        {
			restring[j++] = input[i];
            i++;
			if (input[i] == ' ')
			{
				flag_space = !flag_space;
				break;
			}
        }
        if(input[i] == ' ' && flag_space)
		{
            flag_space = !flag_space;
            restring[j++] = input[i];
        }
        if(input[i] == '\0')
            break;
        i++;
	}
	restring[j] = '\0';
	return (restring);
}
