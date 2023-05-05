/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:43:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/05 22:34:29 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract(t_components *node, t_env *env)
{
	int		i;
	char	*join;
	t_node	*tmp;
	char	**spliting;
	char	*concat;
	char 	*ss1;
	char 	*temp;

	concat = ft_strdup("");
	temp = ft_strdup(node->token);
	i = 0;
	tmp = env->env->top;
	if (node->token[0] != '$')
		join = ft_strtok(node->token, "$");
	ss1 = ft_strchr(temp, '$');
	spliting = ft_split(ss1, '$');
	while (spliting[i] != NULL)
	{	
		while (tmp)
		{
			if (!ft_strcmp(spliting[i], tmp->key))
				concat = ft_strjoin(concat, tmp->value);
			tmp = tmp->next;
		}
		tmp = env->env->top;
		i++;
	}
	free(temp);
	if (!join && !concat)
		return ("");
	if (!join)
		return (concat);
	join = ft_strdup("");
	return (ft_strjoin(join, concat));
}