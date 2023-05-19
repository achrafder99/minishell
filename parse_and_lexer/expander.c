/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 13:36:44 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_dollar_sign(t_components *components, t_env *env, t_info *info,
		t_components *components1)
{
	char	*temp;
	char	*token;
	char	**spliting;
	int		i;

	token = components->token;
	if (token[0] != '\'' && token[ft_strlen(token) - 1] != '\'')
	{
		components->token = ft_strtrim(components->token, "\"");
		temp = extract(components, env, info);
		if (temp)
		{
			spliting = ft_split(temp, ' ');
			push(&components1, spliting[0], components->type.type);
			i = 0;
			while (spliting[++i])
				push(&components1, spliting[i], "ARG");
			free(temp);
		}
		else
			push(&components1, "", components->type.type);
	}
	else
		push(&components1, ft_strtrim(token, "\'\""), components->type.type);
}

void	expander(t_components *node,
				t_env *env,
				t_info *info)
{
	t_components	*components;
	t_components	*components1;
	char			*token;

	components1 = NULL;
	components = node;
	while (components != NULL)
	{
		if (ft_strchr(components->token, '*')
			&& check_is_matched(components->token))
			extract_matched_file(components->token, components->type.type, \
			&components1);
		else if (ft_strchr(components->token, '$')
			&& ft_strcmp(components->type.type, "END_HEREDOC"))
			extract_dollar_sign(components, env, info, components1);
		else
		{
			token = ft_strtrim(components->token, "\'\"");
			push(&components1, token, components->type.type);
			free(token);
		}
		components = components->next;
	}
	return (parser(components1, info, env), free_node(components1));
}
