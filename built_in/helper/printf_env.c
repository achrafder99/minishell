/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:09:18 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 02:39:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_car(char *string)
{
	if (*string == '\\')
	{
		string++;
		if (*string == '\'' || *string == '\"' || *string == '$'
			|| *string == ';' || *string == '|' || *string == '<'
			|| *string == '>' || *string == '&')
			write(1, string, 1);
		else
			write(1, string - 1, 2);
	}
	else
		write(1, string, 1);
}

void	print_env(char *string, t_info *info)
{
	int		i;
	char	**spliting;
	char	*value;

	while (*string != '\0' && *string != '$')
	{
		print_car(string);
		string++;
	}
	spliting = ft_split(string, '$');
	i = -1;
	while (spliting[++i])
	{
		if (spliting[i][0] == '?')
			write(1, &spliting[i][1], ft_strlen(spliting[i]) - 1);
		else
		{
			value = getenv(spliting[i]);
			if (value)
				write(1, value, ft_strlen(value));
		}
	}
	free_things(spliting);
}
