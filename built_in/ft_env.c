/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:51 by aalami            #+#    #+#             */
/*   Updated: 2023/04/05 15:02:26 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst   *get_env(char **env)
{
	t_lst   *env_lst;

	env_lst = creat_list();
	push_list(env_lst, env);
	return (env_lst);
}

void    ft_env(char **env)
{
   t_lst	*env_lst;
	t_node *tmp;

	env_lst = get_env(env);
	tmp = env_lst->top;
	while (tmp)
	{
		printf("%s\n",tmp->data);
		tmp = tmp->next;
	}
}