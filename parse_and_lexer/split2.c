/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:00:29 by adardour          #+#    #+#             */
/*   Updated: 2023/05/10 22:55:27 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_2(char *input)
{
	int		count;
	int		i;
	char	*string;
	char	**result;
	char	*token;

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
	free(string);
	return (result);
}
