/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:00:29 by adardour          #+#    #+#             */
/*   Updated: 2023/05/05 19:04:03 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **split_2(char *input)
{
    char *string;
    int count;
    char **result;
	char *token;
	int i;
	
	string = ft_strdup(input);
    result = (char **)malloc(sizeof(char *) * (number_of_token(input) + 1));
    if (!result)
    {
        perror("");
        exit(1);
    }
	i = 0;
	token = ft_strtok(string, " ");
    while (token != NULL)
    {
		result[i] = ft_strdup(token);
        i++;
        token = ft_strtok(NULL, " ");
    }
    result[i] = NULL;
    return (result);
}