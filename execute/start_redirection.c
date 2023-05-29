/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/05/29 23:35:23 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_out(t_command *cmd)
{
	int	fd;
	int	new_fd;

	fd = 1;
	if (!ft_strcmp(cmd->out_type, "REDIRECT_out"))
		fd = open(cmd->last_out, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		fd = open(cmd->last_out, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("");
		return (fd);
	}
	new_fd = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	complet_redirect_in(int fd)
{
	if (fd == -1)
		perror("error occurred");
	return (dup2(fd, STDIN_FILENO));
}

int	redirect_in(t_command *cmd, t_here_data *data_lst)
{
	int	fd;
	int	new_fd;

	fd = 1;
	if (!ft_strcmp(cmd->in_type, "REDIRECT_in"))
	{
		fd = open(cmd->last_in, O_RDWR, 0777);
		complet_redirect_in(fd);
	}
	else if (!ft_strcmp(cmd->in_type, "HEREDOC") && data_lst)
	{
		save_heredoc_data(data_lst);
		fd = open(".heredoc", O_RDWR, 0777);
		new_fd = complet_redirect_in(fd);
	}
	if (fd != -1)
		close(fd);
	return (fd);
}

int	redirection(t_command *cmd, t_here_data *data_lst, t_info *info)
{
	t_command	*l_fs;

	l_fs = cmd;
	info->fd_out = -2;
	info->fd_in = -2;
	if (check_rederict_out(cmd) && (!ft_strcmp(l_fs->out_type, "REDIRECT_out")
			|| !ft_strcmp(l_fs->out_type, "APPEND_MODE")))
		info->fd_out = redirect_out(l_fs);
	if (check_rederict_in(cmd))
		info->fd_in = redirect_in(cmd, data_lst);
	if (info->fd_in == -1 || info->fd_out == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}
