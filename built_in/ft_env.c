/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:51 by aalami            #+#    #+#             */
/*   Updated: 2023/04/06 21:27:30 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst   *get_env(char **env)
{
	t_lst   *env_lst;

	env_lst = creat_list();
	push_list(env_lst, env);
	env_lst->flag = 0;
	return (env_lst);
}

void    ft_env(t_lst *env_lst)
{
	t_node *tmp;

	tmp = env_lst->top;
	while (tmp)
	{
		printf("%s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
}