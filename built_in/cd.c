/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/05/25 18:09:42 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	back_to_home(t_env *env)
{
	char	*home_dir;
	t_node	*tmp;

	tmp = env->env->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		home_dir = ft_strdup(tmp->value);
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	update_dir(env, 0);
	if (chdir(home_dir) == -1)
		perror(home_dir);
	update_dir(env, 1);
	free(home_dir);
	return (0);
}

char	*get_old_and_pwd_value(t_lst *env, int flag)
{
	t_node	*node;

	node = env->top;
	while (node)
	{
		if (!ft_strcmp(node->key, "OLDPWD") && !flag)
			break ;
		if (!ft_strcmp(node->key, "PWD") && flag)
			break ;
		node = node->next;
	}
	if (node)
		return (node->value);
	else
		return (0);
}

int	switch_dr(t_env *env)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = ft_strdup(get_old_and_pwd_value(env->env, 0));
	pwd = get_old_and_pwd_value(env->env, 1);
	if (oldpwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	else
	{
		update_dir(env, 0);
		chdir(oldpwd);
		if (pwd)
			update_dir(env, 1);
		printf("%s\n", oldpwd);
		free(oldpwd);
	}
	return (0);
}

int	cd(t_command *cmd, t_env *env)
{
	if (cmd->argc == 0 || !ft_strcmp(cmd->args[0], "~"))
		return (back_to_home(env));
	else if (!ft_strcmp(cmd->args[0], "-"))
		return (switch_dr(env));
	else if (access(cmd->args[0], F_OK) != -1)
	{
		update_dir(env, 0);
		if (chdir(cmd->args[0]) == -1)
		{
			perror(cmd->args[0]);
			return (1);
		}
		update_dir(env, 1);
		return (0);
	}
	else
	{
		if (chdir(cmd->args[0]) == -1)
			perror(cmd->args[0]);
		return (1);
	}
}
