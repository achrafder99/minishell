/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:49:16 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 12:59:31 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_components **node)
{
	int				number_of_args;
	t_components	*temp;

	number_of_args = 0;
	temp = *node;
	while (temp && ft_strcmp(temp->type.type, "PIPE"))
	{
		if ((!ft_strcmp(temp->type.type, "OPTION")
				|| !ft_strcmp(temp->type.type, "ARG")))
			number_of_args++;
		temp = temp->next;
	}
	return (number_of_args);
}

char	**init_allocation(t_components **node)
{
	char	**args;
	int		number_of_args;

	number_of_args = count_args(node);
	args = (char **)malloc((sizeof(char *) * number_of_args) + 1);
	if (!args)
	{
		perror("");
		exit(1);
	}
	return (args);
}

char	**found_args(t_components **node)
{
	t_components	*temp;
	char			*temp_string;
	char			**args;
	int				i;

	args = init_allocation(node);
	temp = *node;
	i = 0;
	while (temp && i < count_args(node) && ft_strcmp(temp->type.type, "PIPE"))
	{
		if ((!ft_strcmp(temp->type.type, "OPTION")
				|| !ft_strcmp(temp->type.type, "ARG")))
		{
			temp_string = cut_string(temp->token);
			if (ft_strlen(temp_string) == 0)
			{
				args[i++] = ft_strdup(" ");
				free(temp_string);
			}
			else
				args[i++] = temp_string;
		}
		temp = temp->next;
	}
	return (args[i] = NULL, args);
}
