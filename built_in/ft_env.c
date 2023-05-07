/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:51 by aalami            #+#    #+#             */
/*   Updated: 2023/05/03 15:12:14 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst   *get_env(char **env)
{
	t_lst   *env_lst;

	env_lst = creat_list();
	if (env_lst)
	{
		push_list(env_lst, env);
		env_lst->flag = 0;
	}
	return (env_lst);
}

int  ft_env(t_lst *env_lst)
{
	t_node *tmp;

	tmp = env_lst->top;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}