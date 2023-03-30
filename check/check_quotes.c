/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:53:27 by adardour          #+#    #+#             */
/*   Updated: 2023/03/29 02:53:37 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quotes(char *input){
	int i;
	i = 0;
	int single;
	int double_q;
	single  = 0;
	double_q  = 0;
	while (input[i] != '\0')
	{
		if((input[i] == '\'' || input[i] == '\"') && input[i - 1] != '\\'){
			if(input[i] == '\'')
					single++;
			else
				double_q++;
		}
		i++;
	}
	if(single % 2 != 0 || double_q % 2 != 0)
			return (0);
	return (1);
}