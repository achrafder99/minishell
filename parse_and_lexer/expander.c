/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/08 19:13:25 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    expander(t_components *node, \
t_env *env, t_info *info)
{
	t_components			*components;
	char					*temp;
	t_components			*tmp;
	t_components			*components1;
	char					**spliting;
	int						i;
	int						position;

	components1 = NULL;
	position = 0;
	components = node;
	tmp = node;
	while (components != NULL)
	{
		if (ft_strchr(components->token, '$') \
		&& ft_strcmp(components->type.type, "END_HEREDOC"))
		{
			temp = extract(components, env);
			if (temp)
			{
				spliting = ft_split(temp, ' ');
				push(&components1, spliting[0], components->type.type);
				i = 1;
				while (spliting[i])
				{
					push(&components1, spliting[i], "ARG");
					i++;
				}
			}
			else
				push(&components1, "", components->type.type);
		}
		else
			push(&components1, components->token, components->type.type);
		components = components->next;
	}
	components = components1;
	// while (components != NULL)
	// {
	// 	printf("Token (%s) Type (%s)\n", components->token, \
	// 	components->type.type);
	// 	components = components->next;
	// }
	// return ;
	parser(components1, info, env);
}
