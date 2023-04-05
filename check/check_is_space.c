/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:51:25 by adardour          #+#    #+#             */
/*   Updated: 2023/04/05 03:44:58 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_is_space(char *input)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		if (includes(input[i]) && input[i + 1] != '>')
		{
			if(input[i + 1] != ' ' || input[i - 1] != ' ')
				count++;
		}
		else
		{
			if (input[i + 1] == '>')
			{
				count++;
				i += 2;
			}
			else if(input[i + 1] == '<')
			{
				count++;
				i += 2;
			}
		}
		i++;
	}
	return (count);
}