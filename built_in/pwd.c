/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:28:19 by adardour          #+#    #+#             */
/*   Updated: 2023/03/14 15:47:38 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_tokens *tokens)
{
	char *buf;
	char *err;
	char **command_line;
	char *pwd;
	int how_many_argument;
	char *print_error;

	pwd = malloc(MAX_PATH_LENGTH);
	if (pwd == NULL)
		return ;
	if (getcwd(pwd, MAX_PATH_LENGTH) == NULL)
		return ;
	if (get_size(tokens) >= 1)
	{
		char *error;
		error = "pwd: too many arguments\n";
		write(2, error, ft_strlen(error));
		return ;
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}