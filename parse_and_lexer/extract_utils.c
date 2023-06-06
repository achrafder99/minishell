/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:59 by adardour          #+#    #+#             */
/*   Updated: 2023/06/06 19:51:37 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free1(char *substr, char *concat)
{
	if (substr)
	{
		free(substr);
		substr = NULL;
	}
	if (concat)
	{
		free(concat);
		concat = NULL;
	}
}

void	free_2(char *result, char *concat)
{
	if (result)
	{
		free(result);
		result = NULL;
	}
	if (concat)
	{
		free(concat);
		concat = NULL;
	}
}

char	*extract_value(t_info *info, t_env *env, char *token)
{
	char	*concat;
	t_node	*tmp;
	char	*trim;

	(void)info;
	concat = NULL;
	tmp = env->env->top;
	trim = ft_strtrim(token, " ");
	while (tmp)
	{
		if (!ft_strcmp(trim, tmp->key) && tmp->value)
		{
			free(trim);
			trim = NULL;
			concat = tmp->value;
			return (ft_strdup(concat));
		}
		tmp = tmp->next;
	}
	free(trim);
	trim = NULL;
	return (NULL);
}

char	*proccess2(char *token, t_info *info, t_env *env)
{
	char	*substr;
	char	*concat;
	char	*temp;

	temp = NULL;
	if (ft_strlen(token) != ft_strcspn(token, " \"/"))
	{
		substr = malloc(sizeof(char) * (ft_strcspn(token, " \"/") + 1));
		if (!substr)
		{
			perror("");
			exit(1);
		}
		ft_strncpy(substr, token, ft_strcspn(token, " \"/"));
		concat = extract_value(info, env, substr);
		temp = ft_strjoin(concat, token + ft_strcspn(token, " \"/"));
		free1(substr, concat);
		return (temp);
	}
	return (extract_value(info, env, token));
}

char	*proccess(t_env *env, t_info *info, char *ss1)
{
	int		i;
	char	*result;
	char	*concat;
	char	*keys;

	keys = ft_strchr(ss1, '$');
	info->spliting = ft_split(keys, '$');
	concat = NULL;
	result = NULL;
	info->temp = NULL;
	i = -1;
	while (info->spliting[++i])
	{
		result = proccess2(info->spliting[i], info, env);
		info->temp = ft_strjoin(concat, result);
		free_2(result, concat);
		concat = ft_strdup(info->temp);
		if (info->temp)
		{
			free(info->temp);
			info->temp = NULL;
		}
	}
	free_things(info->spliting);
	return (concat);
}
