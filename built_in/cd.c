/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/03/14 00:07:14 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_tokens *tokens)
{
	char *home_dir;
	if (get_size(tokens) == 0 || !ft_strcmp(tokens->next->token, "~"))
	{
		char *home_dir = ft_strjoin("/home/", getenv("USER"));
		chdir(home_dir);
		return ;
	}
	else if (!access(tokens->next->token, F_OK) && get_size(tokens) == 1)
	{
		chdir(tokens->next->token);
		return ;
	}
	else
	{
		write(STDERR_FILENO, tokens->token, ft_strlen(tokens->token));
		write(2, ": ", 2);
		write(2, "no such file or directory",
				ft_strlen("no such file or directory"));
		write(2, " :", 2);
		write(2, tokens->next->token, ft_strlen(tokens->next->token));
		write(2, "\n", 1);
	}
}