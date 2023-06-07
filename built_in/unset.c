/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:49:13 by aalami            #+#    #+#             */
/*   Updated: 2023/06/07 01:36:12 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_variable(char *key, t_lst *lst)
{
	t_node	*tmp;
	t_node	*tmp_a;

	tmp = lst->top;
	while (tmp)
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

int	handle_unset_error(char *arg, int i)
{
	if (ft_strlen(arg) != (unsigned int)i)
	{
		ft_putstr_fd("minshell: unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

int	check_valid_id(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 95)
		{
			while ((arg[i] && arg[i] >= 95 && arg[i] <= 122) || (arg[i] >= 65
					&& arg[i] <= 90) || (arg[i] >= 48 && arg[i] <= 57))
				i++;
			break ;
		}
		else
		{
			while ((arg[i] && arg[i] >= 95 && arg[i] <= 122) || (arg[i] >= 65
					&& arg[i] <= 90))
				i++;
			break ;
		}
		i++;
	}
	return (handle_unset_error(arg, i));
}

int	ft_unset(t_command *cmd, t_env *env)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			if (!check_valid_id(cmd->args[i]))
				return (1);
			remove_variable(cmd->args[i], env->exp);
			remove_variable(cmd->args[i], env->env);
			i++;
		}
	}
	return (0);
}
