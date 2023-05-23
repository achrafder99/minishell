/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:51 by aalami            #+#    #+#             */
/*   Updated: 2023/05/23 15:58:46 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	push_list(t_lst *lst, char **env)
{
	int		i;
	t_node	*tmp;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!ft_strcmp(split[0], "SHLVL"))
			split[1] = update_shell_level(split[1]);
		if (split[2])
			tmp = ft_new_node(split[0], get_value(env[i]));
		else
			tmp = ft_new_node(split[0], split[1]);
		ft_lstadd_back(lst, tmp);
		free_things(split);
		i++;
	}
	set_oldpwd(lst);
}

t_lst	*get_env(char **env)
{
	t_lst	*env_lst;

	env_lst = creat_list();
	if (env_lst)
	{
		if (env[0] != NULL && env != NULL)
			push_list(env_lst, env);
		else
			handle_env_not_found(env_lst);
		env_lst->flag = 0;
	}
	return (env_lst);
}

int	ft_env(t_lst *env_lst, t_command *command)
{
	t_node	*tmp;

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
