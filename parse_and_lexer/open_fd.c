/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:44:14 by adardour          #+#    #+#             */
/*   Updated: 2023/05/29 22:55:31 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_in(t_command *command)
{
	char	*error;
	int		fd;

	fd = open(command->last_in, O_RDONLY, 0777);
	if (fd == -1)
	{
		error = ": No such file or directory\n";
		write(2, command->last_in, ft_strlen(command->last_in));
		write(2, error, ft_strlen(error));
		return (1);
	}
	close(fd);
	return (0);
}
