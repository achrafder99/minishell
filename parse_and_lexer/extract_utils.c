/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:42:59 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 22:34:04 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_value(t_info *info, t_env *env, char *token)
{
	char	*concat;
	t_node	*tmp;
	char	*trim;
	int		i;

	concat = NULL;
	tmp = env->env->top;
	while (tmp)
	{
		trim = ft_strtrim(token, " ");
		if (!ft_strcmp(trim, tmp->key) && tmp->value)
		{
			concat = tmp->value;
			free(trim);
			return (concat);
		}
		free(trim);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*proccess2(char *token, t_info *info, t_env *env)
{
	int		str_cspn;
	char	*substr;
	char	*concat;
	char	*temp;

	concat = NULL;
	str_cspn = ft_strcspn(token, " \"");
	temp = NULL;
	if (ft_strlen(token) != str_cspn)
	{
		substr = malloc(sizeof(char) * (str_cspn + 1));
		if (!substr)
		{
			perror("");
			exit(1);
		}
		ft_strncpy(substr, token, str_cspn);
		concat = extract_value(info, env, substr);
		free(substr);
		substr = NULL;
		temp = ft_strjoin(concat, token + str_cspn);
	}
	else
		return (extract_value(info, env, token));
	return (temp);
}

char	*proccess(t_env *env, t_info *info, char *ss1)
{
	char	**spliting;
	int		i;
	char	*result;
	char	*temp;

	info->token = ft_strdup("");
	spliting = ft_split(ss1, '$');
	i = 0;
	result = NULL;
	while (spliting[i])
	{
		result = proccess2(spliting[i], info, env);
		if (result)
		{
			temp = ft_strjoin(info->token, result);
			free(info->token);
			info->token = temp;
			free(result);
			result = NULL;
		}
		i++;
	}
	free_things(spliting);
	return (info->token);
}
