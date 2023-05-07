/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_qouted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:51:43 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:06:41 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_qouted(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\'' || string[i] == '\"')
			return (1);
			i++;
	}
	return (0);
}
