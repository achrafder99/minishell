/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:30:13 by aalami            #+#    #+#             */
/*   Updated: 2023/05/23 15:31:17 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = malloc(sizeof(char) * MAX_PATH_LENGTH);
			if (!tmp->value)
				return ;
			tmp->value = getcwd(tmp->value, MAX_PATH_LENGTH);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = malloc(sizeof(char) * MAX_PATH_LENGTH);
			if (!tmp->value)
				return ;
			tmp->value = getcwd(tmp->value, MAX_PATH_LENGTH);
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_dir(t_env *env, int flag)
{
	if (flag == 0)
	{
		update_oldpwd(env->env);
		update_oldpwd(env->exp);
	}
	else
	{
		update_pwd(env->env);
		update_pwd(env->exp);
	}
}
