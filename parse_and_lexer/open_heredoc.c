/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:27:55 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 20:41:16 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_heredoc(char *end)
{
	char	*read_the_line;
	int		fd;

	while (1)
	{
		read_the_line = readline("> ");
		fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			perror("");
			return ;
		}
		if (!strncmp(end, read_the_line, ft_strlen(read_the_line) - 1))
			break ;
		write(fd, read_the_line, ft_strlen(read_the_line));
		write(fd, "\n", 1);
	}
	unlink("/tmp/heredoc");
	close(fd);
}
