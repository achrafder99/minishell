/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:49:16 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 12:53:01 by adardour         ###   ########.fr       */
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
		if (!ft_strcmp(temp->type.type, "OPTION") || !ft_strcmp(temp->type.type,
				"ARG"))
			number_of_args++;
		temp = temp->next;
	}
	return (number_of_args);
}

char	**found_args(t_components **node, char *cmd)
{
	t_components	*temp;
	char			**args;
	int				number_of_args;
	int				i;

	number_of_args = count_args(node);
	temp = *node;
	i = 0;
	args = (char **)malloc((sizeof(char *) * number_of_args) + 1);
	if (!args)
	{
		perror("");
		exit(1);
	}
	while (i < number_of_args && temp && ft_strcmp(temp->type.type, "PIPE"))
	{
		if (!ft_strcmp(temp->type.type, "OPTION") || !ft_strcmp(temp->type.type,
				"ARG"))
		{
			args[i] = ft_strdup(temp->token);
			i++;
		}
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}
