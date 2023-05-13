/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 05:04:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/13 20:24:21 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_redirection(char *symbol)
{
	return (!ft_strcmp(symbol, ">") || !ft_strcmp(symbol, ">>")
		|| !ft_strcmp(symbol, "<") || !ft_strcmp(symbol, "<<"));
}
