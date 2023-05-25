/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:59 by adardour          #+#    #+#             */
/*   Updated: 2023/05/25 21:40:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free1(char *substr, char *concat)
{
	free(substr);
	substr = NULL;
	free(concat);
	concat = NULL;
}

char	*extract_value(t_info *info, t_env *env, char *token)
{
	char	*concat;
	t_node	*tmp;
	char	*trim;
	int		i;

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
	if (ft_strlen(token) != ft_strcspn(token, " \""))
	{
		substr = malloc(sizeof(char) * (ft_strcspn(token, " \"") + 1));
		if (!substr)
		{
			perror("");
			exit(1);
		}
		ft_strncpy(substr, token, ft_strcspn(token, " \""));
		concat = extract_value(info, env, substr);
		if (concat == NULL)
		{
			free(substr);
			return (NULL);
		}
		temp = ft_strjoin(concat, token + ft_strcspn(token, " \""));
		free1(substr, concat);
		return (temp);
	}
	return (extract_value(info, env, token));
}

char	*proccess(t_env *env, t_info *info, char *ss1)
{
	int		i;
	char	*result;
	char	**split_keys;
	char	*concat;
	char	*keys;

	keys = ft_strchr(ss1, '$');
	split_keys = ft_split(keys, '$');
	concat = NULL;
	result = NULL;
	i = 0;
	while (split_keys[i])
	{
		if (result)
		{
			free(result);
			result = NULL;
		}
		result = proccess2(split_keys[i], info, env);
		concat = ft_strjoin(concat, result);
		i++;
	}
	free_things(split_keys);
	return (concat);
}
