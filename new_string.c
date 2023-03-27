/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:48:13 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 21:59:41 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char *new_str(char *str,int count){
    int i;
    i = 0;

    int j;
    j = 0;
    
    char *new_str;
    int length = ft_strlen(str) + count * 2;
    new_str = malloc(length + 1);
    while (i < length - 1)
    {
        if(str[i] == '>' && str[i + 1] == '>'){
            new_str[j] = ' ';
            j++;
            new_str[j] = '>';
            j++;
            new_str[j] = '>';
            j++;
            new_str[j] = ' ';
            i++;
        }
		else if(str[i] == '<' && str[i + 1] == '<'){
            new_str[j] = ' ';
            j++;
            new_str[j] = '<';
            j++;
            new_str[j] = '<';
            j++;
            new_str[j] = ' ';
            i++;
        }
        else{
			if(includes(str[i])){
                new_str[j] = ' ';
                j++;
                new_str[j] = str[i];
                j++;
                new_str[j] = ' ';
            }
			else
				new_str[j] = str[i];
		}
        i++;
        j++;
    }

    return (new_str);
}
