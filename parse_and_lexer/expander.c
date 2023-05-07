/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/07 02:03:18 by adardour         ###   ########.fr       */
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
	new_node->token = ft_strdup(token);
	new_node->type.type = ft_strdup(type);

	current_node = *head_ref;
	i = 0;
	while (i < position && current_node != NULL)
	{
		current_node = current_node->next;
		i++;
	}
	new_node->next = current_node->next;
	current_node->next = new_node;
}

void	add_token(t_components *node, int position, char *token)
{
	t_components	*temp;
	int				i;

	i = 0;
	temp = node;
	while (temp && i < position)
	{	
		temp = temp->next;
		i++;
	}
	if (temp != NULL)
		temp->token = token;
}

int	get_size_nodes(t_components *node)
{
	t_components	*temp;
	int				size;

	size = 0;
	temp = node;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	after(t_components *node,int position)
{
	t_components *tt;
	tt = node;
	printf("====== %d ========= \n",position);
	while (node != NULL)
	{
		printf("Node (%s) Type (%s)\n",node->token,node->type.type);
		node = node->next;
	}
}

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
		if (ft_strchr(components->token, '$'))
		{
			temp = extract(components, env);
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
			push(&components1, components->token, components->type.type);
		components = components->next;
	}
	// printf("size :%d\n", get_size_nodes(node));
	// components = components1;
	// while (components != NULL)
	// {
	// 	printf("Token (%s) Type (%s)\n", components->token, \
	// 	components->type.type);
	// 	components = components->next;
	// }
	// return ;
	parser(components1, info, env);
}
