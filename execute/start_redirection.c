/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/05/28 00:52:44 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_out(t_command *cmd)
{
	int	fd;

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
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

void	complet_redirect_in(int fd)
{
	if (fd == -1)
		perror("error occurred");
	dup2(fd, STDIN_FILENO);
}

int	redirect_in(t_command *cmd, t_here_data *data_lst)
{
	int	fd;

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
		complet_redirect_in(fd);
	}
	if (fd != -1)
		close(fd);
	return (fd);
}

int	redirection(t_command *cmd, t_here_data *data_lst)
{
	int			fd_in;
	int			fd_out;
	t_command	*l_fs;

	l_fs = cmd;
	fd_in = 0;
	fd_out = 0;
	if (check_rederict_out(cmd) && (!ft_strcmp(l_fs->out_type, "REDIRECT_out")
			|| !ft_strcmp(l_fs->out_type, "APPEND_MODE")))
		fd_out = redirect_out(l_fs);
	if (check_rederict_in(cmd))
		fd_in = redirect_in(cmd, data_lst);
	if (fd_in == -1 || fd_out == -1)
		return (-1);
	return (0);
}
