/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 02:38:29 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 21:59:24 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_things(char **spliting)
{
	int	i;

	i = 0;
	if (spliting == NULL)
		return ;
	while (spliting[i])
	{
		free(spliting[i]);
		i++;
	}
	free(spliting);
	spliting = NULL;
}
