/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:08:25 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:51:42 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wildcard(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_strstr(argv[i], "*") && match_file(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
