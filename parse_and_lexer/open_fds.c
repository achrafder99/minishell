/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:04:02 by adardour          #+#    #+#             */
/*   Updated: 2023/05/28 01:23:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_fds(const char *type, const char *filename, int *fd)
{
	char	*clear_file_name;

	clear_file_name = NULL;
	if (!ft_strcmp(type, "REDIRECT_out"))
	{
		*fd = open(clear_file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
			return (perror("error occurred."), -1);
		write(*fd, "", 1);
	}
	else if (!ft_strcmp(type, "REDIRECT_in"))
	{
		*fd = open(filename, O_RDWR | O_TRUNC, 0644);
		if (*fd == -1)
			return (printf("tsh: %s: No such file or directory\n", filename),
				(1));
	}
	else if (!ft_strcmp(type, "APPEND_MODE"))
	{
		*fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
			return (perror("error occurred."), -1);
	}
	return (0);
}
