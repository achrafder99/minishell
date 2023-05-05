/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/06 00:22:25 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_components **head_ref, char *token, char *type, int position)
{
	t_components	*current_node;
	t_components	*new_node;
	int				i;

	new_node = (t_components *)malloc(sizeof(t_components));
	if (!new_node)
	{
		perror("");
		return ;
	}
	new_node->token = token;
	new_node->type.type = type;

	current_node = *head_ref;
	i = 1;
	while (i < position && current_node != NULL)
	{
		current_node = current_node->next;
		i++;
	}
	new_node->next = current_node->next;
	current_node->next = new_node;
}

void    expander(t_components *node, t_env *env, t_info *info)
{
	t_components	*components;
	char			*temp;
	char			**spliting;
	int				i;
	int				position;

	position = 0;
	components = node;
	while (node != NULL)
	{
		if (ft_strchr(node->token, '$'))
		{
			temp = extract(node, env);
			spliting = ft_split(temp, ' ');
			node->token = spliting[0];
			i = 1;
			while (spliting[i])
			{	
				add_node(&components, spliting[i], "ARG", position);
				position++;
				i++;
			}
		}
		position++;
		node = node->next;
	}
	parser(components, info, env);
}
