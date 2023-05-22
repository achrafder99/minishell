/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:43:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 15:37:59 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_exit_status(char *string, t_info *info)
{
	int		i;
	int		length;
	int		j;
	char	*status_exit;
	char	*str;

	status_exit = ft_strdup(ft_itoa(info->status_code));
	length = (ft_strlen(string) - 1) + ft_strlen(status_exit);
	str = malloc(sizeof(char) * (length + 1));
	i = 0;
	while ((size_t)i < ft_strlen(status_exit))
	{
		str[i] = status_exit[i];
		i++;
	}
	j = 1;
	while (string[j] != '\0')
	{
		str[i] = string[j];
		j++;
		i++;
	}
	str[length] = '\0';
	return (str);
}

char	*extract_value(t_info *info, t_env *env, char **spliting)
{
	char	*concat;
	t_node	*tmp;
	int		i;

	concat = "";
	i = 0;
	tmp = env->env->top;
	while (spliting[i] != NULL)
	{
		if (ft_strchr(spliting[i], '?'))
			concat = ft_strjoin(concat, get_exit_status(spliting[i], info));
		while (tmp)
		{
			if (!ft_strcmp(spliting[i], tmp->key) && tmp->value)
			{
				concat = ft_strjoin(concat, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = env->env->top;
		i++;
	}
	free_things(spliting);
	return (concat);
}

char	*until_dollar_sign(char *token)
{
	char	*before_dollar;
	int		string_size;

	string_size = ft_strcspn(token, "$");
	before_dollar = malloc((sizeof(char) * string_size) + 1);
	if (!before_dollar)
	{
		perror("");
		exit(1);
	}
	ft_strncpy(before_dollar, token, string_size);
	return (before_dollar);
}

char	*proccess(char *token, t_env *env, t_info *info)
{
	char	*concat;
	char	*ss1;
	char	**spliting;

	ss1 = ft_strchr(token, '$');
	spliting = ft_split(ss1, '$');
	concat = extract_value(info, env, spliting);
	return (concat);
}

char	*extract(char *compo, t_env *env, t_info *info)
{
	char	*join;
	char	*ss1;
	char	*concat;
	char	*token;

	token = ft_strdup(compo);
	join = NULL;
	if (compo[0] != '$')
		join = until_dollar_sign(compo);
	concat = proccess(token, env, info);
	if (concat == NULL || ft_strlen(concat) == 0)
	{
		free(token);
		return (NULL);
	}
	if (!join)
	{
		free(token);
		return (concat);
	}
	free(token);
	token = ft_strjoin(join, concat);
	free(join);
	free(concat);
	return (token);
}
