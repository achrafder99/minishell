/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 23:31:24 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_rederict_in(t_command *cmd)
{
	if (cmd->last_in)
		return (1);
	return (0);
}

int	check_rederict_out(t_command *cmd)
{
	if (cmd->last_out)
		return (1);
	return (0);
}

int	save_heredoc_data(t_command *cmd, t_here_data *data_lst)
{
	t_here_node	*tmp;
	int fd;

	fd =  open(".heredoc", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		return (fd);
	tmp = data_lst->top;
	while (tmp)
	{
		write(fd, tmp->data, ft_strlen(tmp->data));
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
	close(fd);
		return (fd);
}

int	redirect_out(t_command *cmd)
{
	int	fd;

	fd = 1;
	if (!ft_strcmp(cmd->out_type, "REDIRECT_out"))
		fd = open(cmd->last_out, O_CREAT | O_RDWR | O_TRUNC , 0777);
	else
		fd = open(cmd->last_out, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("error occurred");
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
		save_heredoc_data(cmd, data_lst);
		fd = open(".heredoc", O_RDWR, 0777);
		complet_redirect_in(fd);
	}
	if (fd != -1)
		close (fd);
	return (fd);
}

int	redirection(t_command *cmd, t_here_data *data_lst)
{
	int	fd_in;
	int	fd_out;
	t_command *l_fs;

	l_fs = cmd;
	if (check_rederict_out(cmd) && (!ft_strcmp(l_fs->out_type, "REDIRECT_out") \
	|| !ft_strcmp(l_fs->out_type, "APPEND_MODE")))
		fd_out = redirect_out(l_fs);
	if (check_rederict_in(cmd))
		fd_in = redirect_in(cmd, data_lst);
	if (fd_in == -1 || fd_out == -1)
		return (-1);
	return (0);
}
