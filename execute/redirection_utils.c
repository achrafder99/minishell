/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:42:46 by aalami            #+#    #+#             */
/*   Updated: 2023/05/29 20:54:30 by aalami           ###   ########.fr       */
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

int	save_heredoc_data(t_here_data *data_lst)
{
	t_here_node	*tmp;
	int			fd;

	fd = open(".heredoc", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
	{
		if (unlink (".heredoc") == -1)
			perror("unlink");
		fd = open(".heredoc", O_CREAT | O_RDWR, 0777);
	}
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
