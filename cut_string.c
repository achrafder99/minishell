/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 04:59:19 by adardour          #+#    #+#             */
/*   Updated: 2023/04/06 03:24:14 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int        count_quotes(char *s)
{
    int    count;
    int    i;

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

char *cut_string(char *s)
{
    int i;
    int j;
	
	i = 0;
	j = 0;
    int size = ft_strlen(s) - count_quotes(s);
    char *s1 = malloc(sizeof(char) * (size + 1));
    if(!s1)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '\"' || s[i] == '\'')
        {
            i++;
            continue;
        }
        s1[j] = s[i];
        i++;
        j++;
    }
    s1[j] = '\0';
    return s1;
}