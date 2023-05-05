/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:59:32 by adardour          #+#    #+#             */
/*   Updated: 2023/04/03 18:06:25 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_redirect(t_command *command)
{
	if (command->infile || command->outfile || command->append_mode)
		return (1);
	return (0);
}
