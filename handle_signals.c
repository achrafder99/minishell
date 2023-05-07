/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:03:07 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 23:05:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	handle_signals(int sign)
{
	char	*username;
	char	*full_username;

	username = ft_strjoin(getenv("USER"), "@:");
	full_username = ft_strjoin(username, "user > ");
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		write(1, full_username, ft_strlen(full_username));
	}
	free(username);
	free(full_username);
}
