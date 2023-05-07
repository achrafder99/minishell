/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:14:19 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 22:51:04 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	number_of_file(char **argv)
{
	int	i;
	int	number_of_file;

	i = 0;
	number_of_file = 0;
	while (argv[i] != NULL)
	{
		if (ft_strstr(argv[i], "*"))
			number_of_file += match_file(argv[i]);
		i++;
	}
	return (number_of_file);
}
