/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:18:23 by adardour          #+#    #+#             */
/*   Updated: 2023/05/11 17:31:04 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_file(t_command *command, t_fds *fds)
{
	fds->fd_append = 0;
	fds->fd_in = 0;
	fds->fd_out = 0;
	// if (command->outfile || command->append_mode || command->infile)
	// {
	// 	if (command->outfile)
	// 		fds->fd_out = open(command->outfile, O_RDWR | O_TRUNC, 0777);
	// 	else if (command->append_mode)
	// 		fds->fd_append = open(command->append_mode, O_RDWR \
	// 		| O_APPEND, 0777);
	// 	else
	// 		fds->fd_in = open(command->infile, O_RDWR, 0777);
	// }
}
