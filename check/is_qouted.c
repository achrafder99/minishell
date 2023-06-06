/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_qouted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:51:43 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 19:47:39 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_qoutes(char *string)
{
	int		i;
	char	qoute;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
		{
			qoute = string[i];
			i++;
			while (string[i] != qoute && string[i] != '\0')
				i++;
			if (string[i] == '\0')
				return (0);
		}
		if (string[i] == '\0')
			break ;
		i++;
	}
	return (1);
}

int	check_if_qouted(t_components *node)
{
	t_components	*temp;

	temp = node;
	while (temp)
	{
		if (!check_qoutes(temp->token))
			return (0);
		temp = temp->next;
	}
	return (1);
}
