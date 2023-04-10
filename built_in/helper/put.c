/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:12:22 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 02:33:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put(char *string)
{
	while (*string)
	{
		write(1, string, 1);
		string++;
	}
	write(1, " ", 1);
}

void	ft_put_echo(char *string)
{
	while (*string)
	{
		if (*string == '\\')
		{
			string++;
			if (*string == '\'' || *string == '\"' || *string == '$'
				|| *string == ';' || *string == '|' || *string == '<'
				|| *string == '>' || *string == '&')
				write(1, string, 1);
			else
				write(1, string - 1, 2);
		}
		else
			write(1, string, 1);
		string++;
	}
}
