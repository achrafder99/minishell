/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:58:32 by adardour          #+#    #+#             */
/*   Updated: 2023/06/04 22:23:36 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**get_argv(t_command *command, int number_arg)
{
	char	**argv;
	int		full_size;
	int		i;
	int		j;

	full_size = number_arg + 1;
	argv = malloc((sizeof(char **) * full_size) + 1);
	if (!argv)
		return (printf("error\n"), (NULL));
	argv[0] = ft_strdup(command->name);
	i = 1;
	j = 0;
	while (i <= number_arg)
	{
		if (ft_strlen(command->args[j]))
		{
			argv[i] = ft_strdup(command->args[j]);
			i++;
			j++;
		}
		else
			j++;
	}
	argv[full_size] = NULL;
	return (argv);
}
