/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:49:48 by aalami            #+#    #+#             */
/*   Updated: 2023/05/20 23:13:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_array_elements(char **env, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(env[i]);
	free(env[i]);
	env[i] = ft_strdup(env[j]);
	free(env[j]);
	env[j] = ft_strdup(tmp);
	free(tmp);
}

t_lst	*sort_env(char **env)
{
	int		i;
	int		j;
	t_lst	*exp;

	i = 0;
	exp = creat_list();
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) < 0)
				swap_array_elements(env, i, j);
			j++;
		}
		i++;
	}
	push_list(exp, env);
	return (exp);
}

void	swap_nodes(t_node *tmp_a, t_node *tmp_b, char *tmp_key, char *tmp_value)
{
	tmp_key = ft_strdup(tmp_a->key);
	tmp_value = ft_strdup(tmp_a->value);
	free(tmp_a->key);
	free(tmp_a->value);
	tmp_a->key = ft_strdup(tmp_b->key);
	tmp_a->value = ft_strdup(tmp_b->value);
	free(tmp_b->key);
	free(tmp_b->value);
	tmp_b->key = ft_strdup(tmp_key);
	tmp_b->value = ft_strdup(tmp_value);
	free(tmp_key);
	free(tmp_value);
}

void	sort_exp_list(t_lst *exp)
{
	t_node	*tmp_a;
	t_node	*tmp_b;
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = NULL;
	tmp_value = NULL;
	tmp_a = exp->top;
	while (tmp_a)
	{
		tmp_b = exp->top;
		while (tmp_b)
		{
			if (ft_strcmp(tmp_a->key, tmp_b->key) < 0)
				swap_nodes(tmp_a, tmp_b, tmp_key, tmp_value);
			tmp_b = tmp_b->next;
		}
		tmp_a = tmp_a->next;
	}
}

int	ft_export(t_command *cmd, t_env *env)
{
	t_node	*tmp;
	t_lst	*lst;

	lst = env->exp;
	if (cmd->argc)
		return (if_valid_identifier(cmd->args, env));
	sort_exp_list(lst);
	tmp = lst->top;
	while (tmp)
	{
		if (tmp->value == NULL)
		{
			if (!lst->flag)
				printf("declare -x %s\n", tmp->key);
		}
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
