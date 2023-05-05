/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/05/01 13:25:58 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	complete_redirect(t_command *cmd, int last)
{
	int	fd;
	if (last == 1)
	{
		if (cmd->infile)
		{
			fd = open(cmd->infile, O_RDWR, 0777);
			if (fd == -1)
				return (perror("error occurred"));
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("error occurred"));
			close(fd);
		}	
	}
	else if (last == 0)
	{
		if (cmd->outfile || cmd->append_mode)
		{
			if (cmd->outfile)
				fd = open(cmd->outfile, O_RDWR, 0777);
			else
				fd = open(cmd->outfile, O_RDWR | O_APPEND, 0777);
			if (fd == -1)
				return (perror("error occurred"));
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (perror("error occurred"));
			close(fd);
		}	
		
	}
}
void	redirection(t_command *cmd, char *type, char *filename, t_fds *fds)
{
	int	fd;
	int	last;

	last = -1;
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
		last = 1;
	}
	if (!ft_strcmp(type, "REDIRECT_in"))
	{
		fd = open(filename, O_RDWR, 0777);
		if (fd == -1)
			return (perror("error occurred"));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("error occurred"));
		close(fd);
		last = 0;
	}
	complete_redirect(cmd, last);
}
