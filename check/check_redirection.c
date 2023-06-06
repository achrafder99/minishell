/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 05:04:18 by adardour          #+#    #+#             */
/*   Updated: 2023/06/05 13:01:42 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_redirection(char *symbol)
{
	if (symbol == NULL)
		return (0);
	return (!ft_strcmp(symbol, ">") || !ft_strcmp(symbol, ">>")
		|| !ft_strcmp(symbol, "<") || !ft_strcmp(symbol, "<<"));
}
