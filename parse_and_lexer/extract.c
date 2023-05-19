/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:43:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 13:56:59 by adardour         ###   ########.fr       */
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
	while (i < ft_strlen(status_exit))
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

char	*extract(t_components *node, t_env *env, t_info *info)
{
	int		i;
	char	*join;
	t_node	*tmp;
	char	**spliting;
	char	*concat;
	char	*ss1;
	char	*temp;

	concat = ft_strdup("");
	temp = ft_strdup(node->token);
	i = 0;
	tmp = env->env->top;
	if (node->token[0] != '$')
		join = ft_strtok(node->token, "$");
	ss1 = ft_strchr(temp, '$');
	spliting = ft_split(ss1, '$');
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
	free(temp);
	if (ft_strlen(concat) == 0)
		return (NULL);
	if (!join)
		return (concat);
	return (ft_strjoin(join, concat));
}
