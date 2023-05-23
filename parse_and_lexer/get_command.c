/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:30:22 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 20:58:22 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_empty_command(t_components **command, t_components *temp)
{
	int	count;

	count = 0;
	while (command != NULL && ft_strlen((*command)->token) == 0)
	{
		temp = *command;
		*command = (*command)->next;
		count++;
	}
	if (temp)
	{
		free(temp->type.type);
		free(temp->token);
		free(temp);
	}
	return (count);
}

void	remove_empty_command(t_components **components)
{
	t_components	*command;
	char			*type;
	t_components	*temp;
	int				i;

	if ((*components)->next == NULL)
		return ;
	i = 0;
	if (ft_strlen((*components)->token) == 0)
	{
		command = *components;
		type = ft_strdup(command->type.type);
		if (count_empty_command(&command, temp) != 0)
		{
			if (command != NULL)
			{
				free(command->type.type);
				command->type.type = NULL;
				command->type.type = ft_strdup(type);
			}
			free(type);
			*components = command;
		}
	}
}
