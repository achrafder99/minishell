/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:13 by aalami            #+#    #+#             */
/*   Updated: 2023/05/02 13:08:19 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	remove_variable(char *key, t_lst *lst)
{
	t_node	*tmp;
	t_node	*tmp_a;

	tmp = lst->top;
	while(tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->key, key))
		{
			tmp_a = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_a);
		}
		tmp = tmp->next;
	}	
}
int	ft_unset(t_command *cmd, t_env *env)
{
	int	i;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			remove_variable(cmd->args[i],env->exp);
			remove_variable(cmd->args[i],env->env);
			i++;
		}
	}
	return (0);
}