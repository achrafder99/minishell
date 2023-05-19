/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:51 by aalami            #+#    #+#             */
/*   Updated: 2023/05/19 14:03:10 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst	*get_env(char **env)
{
	t_lst	*env_lst;

	env_lst = creat_list();
	if (env_lst)
	{
		push_list(env_lst, env);
		env_lst->flag = 0;
	}
	return (env_lst);
}

int	ft_env(t_lst *env_lst, t_command *command)
{
	t_node *tmp;
	if (command->argc)
		return (1);
	tmp = env_lst->top;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}