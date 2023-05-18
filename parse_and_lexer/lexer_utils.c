/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:13:41 by aalami            #+#    #+#             */
/*   Updated: 2023/05/18 19:15:20 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_push_command(char **spliting, t_components **head, int i,
		t_info *info)
{
	push(head, spliting[0], "COMMAND");
	i = 1;
	while (spliting[i] != NULL)
	{
		if (spliting[i][0] == '-')
			push(head, spliting[i], "OPTION");
		else if (!ft_strcmp(spliting[i], "|"))
		{
			info->flags = 0;
			if (!check_is_redirection(spliting[i + 1]))
				info->flags = 1;
			push_component(head, "PIPE", spliting, &i, info);
		}
		else if (check_is_redirection(spliting[i]))
			redirect_componenets(spliting, &i, head, info);
		else
			push(head, spliting[i], "ARG");
		i++;
	}
}

void	process_push_redirection(char **spliting, t_components **head, int i,
		t_info *info)
{
	while (spliting[i] != NULL)
	{
		if (!ft_strcmp(spliting[i], "|"))
		{
			info->flags = 0;
			push_component(head, "PIPE", spliting, &i, info);
		}
		else if (check_is_redirection(spliting[i]))
		{
			redirect_componenets(spliting, &i, head, info);
			if (spliting[i + 1] != NULL && !info->flags
				&& !check_is_redirection(spliting[i + 1])
				&& ft_strcmp(spliting[i + 1], "|"))
			{
				push(head, spliting[i + 1], "COMMAND");
				i++;
				info->flags = 1;
			}
		}
		else
			push(head, spliting[i], "ARG");
		i++;
	}
}
