/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/04/30 19:44:52 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection(char *type, char *filename, t_fds *fds)
{
	int	fd;
	if (!ft_strcmp(type, "REDIRECT_out") || !ft_strcmp(type, "APPEND_MODE"))
	{
		if (!ft_strcmp(type, "REDIRECT_out"))
			fd = open(filename, O_RDWR, 0777);
		else
			fd = open(filename, O_RDWR | O_APPEND, 0777);
		if (fd == -1)
			return (perror("error occurred"));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("error occurred"));
		close(fd);
	}
	else if (!ft_strcmp(type, "REDIRECT_in"))
	{
		fd = open(filename, O_RDWR, 0777);
		if (fd == -1)
			return (perror("error occurred"));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("error occurred"));
		close(fd);
	}
}
