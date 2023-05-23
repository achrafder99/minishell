/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:34:12 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 20:34:32 by adardour         ###   ########.fr       */
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
			tmp->value = getcwd(tmp->value, 256);
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
			tmp->value = getcwd(tmp->value, 256);
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

void	back_to_home(t_env *env)
{
	char	*home_dir;

	home_dir = ft_strjoin("/Users/", getenv("USER"));
	update_dir(env, 0);
	chdir(home_dir);
	update_dir(env, 1);
	free(home_dir);
}

int	cd(t_command *cmd, t_env *env)
{
	if (cmd->argc == 0 || !ft_strcmp(cmd->args[0], "~"))
	{
		back_to_home(env);
		return (0);
	}
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
