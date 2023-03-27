/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 04:59:19 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 05:00:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char *cut_string(char *s){
	int number_of_quotes;
	number_of_quotes = 0;
	int i;
	i = 0;
	char *s1;
	while (s[i] != '\0')
	{
		if(s[i] == '\'' || s[i] == '\"'){
			number_of_quotes++;
		}
		i++;
	}
	int size;
	size = ft_strlen(s) - number_of_quotes;
	s1 = malloc((sizeof(char) * size) + 1);
	if(!s1)
		return (NULL);
	i = 0;
	
	int j;
	j = 0;
	while (s[j] != '\0')
	{
		if(s[j] == '\'' || s[j] == '\"')
			j++;
		s1[i] = s[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}