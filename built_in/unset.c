/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:13 by aalami            #+#    #+#             */
/*   Updated: 2023/05/06 15:09:45 by adardour         ###   ########.fr       */
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
		if (tmp == lst->top && !ft_strcmp(lst->top->key, key))
		{
			tmp_a = lst->top;
			lst->top = lst->top->next;
			free(tmp_a->key);
			free(tmp_a->value);
			free(tmp_a);
		}
		if (tmp->next && !ft_strcmp(tmp->next->key, key))
		{
			tmp_a = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_a->key);
			free(tmp_a->value);
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