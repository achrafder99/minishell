/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:50:06 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 20:54:44 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		write(1, env[i], ft_strlen(env[i]));
		i++;
	}
	write(1, "\n", 1);
}
