/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/04/16 22:36:36 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char    *new_str(char *input, int count)
{
    int        i;
    int        j;
    int        length;
    char    *restring;
    
    length = strlen(input) + count;
    restring = (char *)malloc(length + 1);
    if (!restring)
    {
        perror("");
        exit(1);
    }
    i = 0;
    j = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\"' || input[i] == '\'')
        {
            while (input[i] != '\0' \
            && (input[i] != '\'' \
            || input[i] != '\"'))
            {
                restring[j] = input[i];
                j++;
                i++;    
            }
        }
        if (includes(input[i]) && (input[i + 1] != '>' && input[i + 1] != '<'))
        {
            if (input[i + 1] == ' ' && input[i - 1] != ' ')
            {
                restring[j] = ' ';
                j++;
                restring[j] = input[i];
                j++;
                i++;
            }
            else if(input[i + 1] != ' ' && input[i - 1] == ' ')
            {
                restring[j + 1] = ' ';
                restring[j] = input[i];
                j +=2;  
                i++;
              
            }
            else if(input[i + 1] != ' ' && input[i - 1] != ' ')
            {
                restring[j] = ' ';
                j++;
                restring[j] = input[i];
                j++;
                restring[j] = ' '; 
                j++;
                i++;
            }
        }
        else if ((input[i] == '>' && input[i + 1] == '>') \
        || (input[i] == '<' && input[i + 1] == '<'))
        {
            if (input[i -1] != ' ' && input[i + 2] == ' ')
            {
                restring[j] = ' ';
                j++;
                restring[j] = input[i];
                j++;
                restring[j] = input[i];
                j++;
                i += 2;
            }
            else if (input[i -1] == ' ' && input[i + 2] != ' ')
            {
                restring[j] = input[i];
                j++;
                restring[j] = input[i];
                j++;
                restring[j] = ' ';
                j++;
                i += 2;
            }
            else if (input[i -1] != ' ' && input[i + 2] != ' ')
            {
                restring[j] = ' ';
                j++;
                restring[j] = input[i];
                j++;
                restring[j] = input[i];
                j++;
                restring[j] = ' ';
                j++;
                i += 2;
            }
        }
        restring[j] = input[i];
        j++;
        i++; 
    }
    restring[j] = '\0';
    return (restring);
}