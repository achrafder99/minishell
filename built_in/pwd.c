/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:28:19 by adardour          #+#    #+#             */
/*   Updated: 2023/05/30 18:38:04 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = malloc(MAX_PATH_LENGTH);
	if (pwd == NULL)
		return (1);
	if (getcwd(pwd, MAX_PATH_LENGTH) == NULL)
	{
		perror("getcwd");
		free (pwd);
		return (1);
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}
