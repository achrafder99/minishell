/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 05:20:50 by adardour          #+#    #+#             */
/*   Updated: 2023/05/11 21:19:30 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// void	complete_redirect(t_command *cmd, int last)
// {
// 	int	fd;
// 	if (last == 1)
// 	{
// 		if (cmd->infile)
// 		{
// 			fd = open(cmd->infile, O_RDWR, 0777);
// 			if (fd == -1)
// 				return (perror("error occurred"));
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 				return (perror("error occurred"));
// 			close(fd);
// 		}	
// 	}
// 	else if (last == 0)
// 	{
// 		if (cmd->outfile || cmd->append_mode)
// 		{
// 			if (cmd->outfile)
// 				fd = open(cmd->outfile, O_RDWR, 0777);
// 			else
// 				fd = open(cmd->outfile, O_RDWR | O_APPEND, 0777);
// 			if (fd == -1)
// 				return (perror("error occurred"));
// 			if (dup2(fd, STDOUT_FILENO) == -1)
// 				return (perror("error occurred"));
// 			close(fd);
// 		}	
		
// 	}
// }
int	check_rederict_in(t_command *cmd)
{
	if (cmd->last->last_in)
		return (1);
	return (0);
}
int	check_rederict_out(t_command *cmd)
{
	if (cmd->last->last_out)
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
void	redirection(t_command *cmd, t_here_data *data_lst)
{
	int	fd;
	t_last_file *l_fs;

	l_fs = cmd->last;
	if (check_rederict_out(cmd) && (!ft_strcmp(l_fs->out_type, "REDIRECT_out") || !ft_strcmp(l_fs->out_type, "APPEND_MODE")))
	{
		if (!ft_strcmp(l_fs->out_type, "REDIRECT_out"))
			fd = open(l_fs->last_out, O_RDWR, 0777);
		else
			fd = open(l_fs->last_out, O_RDWR | O_APPEND, 0777);
		if (fd == -1)
			return (perror("error occurred"));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("error occurred"));
		close(fd);
	}
	if (check_rederict_in(cmd))
	{
		if (!ft_strcmp(l_fs->in_type, "REDIRECT_in"))
		{
			fd = open(l_fs->last_in, O_RDWR, 0777);
			if (fd == -1)
				return (perror("error occurred"));
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("error occurred"));
			close(fd);
		}
		else if (!ft_strcmp(l_fs->in_type, "HEREDOC") && data_lst)
		{
			save_heredoc_data(cmd, data_lst);
			fd = open(".heredoc", O_RDWR, 0777);
			if (fd == -1)
				return (perror("error occurred"));
			if (dup2(fd, STDIN_FILENO) == -1)
				return (perror("error occurred"));
			close (fd);
			
		}
	}
	// complete_redirect(cmd, last);
}
