/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_stars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:16:04 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:50:53 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	number_of_star(char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strstr(argv[i], "*"))
			count++;
		i++;
	}
	return (count);
}
