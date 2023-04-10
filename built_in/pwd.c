/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:28:19 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 21:37:04 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_command *cmd)
{
	char	*buf;
	char	*pwd;

	pwd = malloc(MAX_PATH_LENGTH);
	if (pwd == NULL)
		return (1);
	if (getcwd(pwd, MAX_PATH_LENGTH) == NULL)
		return (1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}
