/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 00:41:30 by aalami           ###   ########.fr       */
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
				return;
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
				return;
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

int	back_to_home(t_env *env)
{
	char	*home_dir;
	t_node	*tmp;
	
	tmp = env->env->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			break;
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
	chdir(home_dir);
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
			break;
		if (!ft_strcmp(node->key, "PWD") && flag)
			break;
		node = node->next;
	}
	return (node->value);
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
		update_dir(env, 1);
		printf("%s\n", oldpwd);
		free(oldpwd);
		return (0);
	}
}
int	cd(t_command *cmd, t_env *env)
{
	if (cmd->argc == 0 || !ft_strcmp(cmd->args[0], "~"))
	{
		return (back_to_home(env));
	}
	else if (!ft_strcmp(cmd->args[0],"-"))
		return (switch_dr(env));
	else if (access(cmd->args[0], F_OK) != -1)
	{
		update_dir(env, 0);
		chdir(cmd->args[0]);
		update_dir(env, 1);
		return (0);
	}
	else
	{
		write(2, "tsh: ", 6);
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": no such file or directory",
			ft_strlen(": no such file or directory"));
		write(2, "\n", 1);
		return (1);
	}
	return (1);
}
