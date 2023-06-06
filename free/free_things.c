/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:38:29 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 20:13:05 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_things(char **spliting)
{
	int	i;

	if (spliting == NULL)
		return ;
	i = 0;
	while (spliting[i])
	{
		free(spliting[i]);
		i++;
	}
	free(spliting[i]);
	free(spliting);
}
