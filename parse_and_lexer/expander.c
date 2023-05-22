/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 15:50:27 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dont_expand(t_components *components, t_components **components1)
{	
	char	*token;

	token = cut_string(components->token);
	push(components1, token, components->type.type);
	free(token);
}

void	split_value(t_components *components, char *temp,
		t_components **components1)
{
	char	**spliting;
	int		i;

	spliting = ft_split(temp, ' ');
	push(components1, spliting[0], components->type.type);
	i = 1;
	while (spliting[i])
	{
		push(components1, spliting[i], "ARG");
		i++;
	}
	free_things(spliting);
}

void	extract_dollar_sign(t_components *components, t_env *env, t_info *info,
		t_components **components1)
{
	char	*temp;
	char	*trim;

	if (components->token[0] != '\''
		&& components->token[ft_strlen(components->token) - 1] != '\'')
	{
		info->token = ft_strtrim(components->token, "\"");
		temp = extract(info->token, env, info);
		if (temp && ft_strlen(temp) > 0)
		{
			split_value(components, temp, components1);
			free(temp);
		}
		else
			push(components1, "", components->type.type);
		free(info->token);
	}
	else
	{
		trim = ft_strtrim(components->token, "\'\"");
		push(components1, trim ,
			components->type.type);
		free(trim);
	}
}

void	expander(t_components *node,
				t_env *env,
				t_info *info)
{
	t_components	*components;
	t_components	*components1;

	components1 = NULL;
	components = node;
	while (components != NULL)
	{
		if (ft_strchr(components->token, '*')
			&& check_is_matched(components->token))
			extract_matched_file(components->token, components->type.type,
				&components1);
		else if (ft_strchr(components->token, '$')
			&& ft_strcmp(components->type.type, "END_HEREDOC")
			&& strcmp(components->token, "$"))
			extract_dollar_sign(components, env, info, &components1);
		else
			dont_expand(components, &components1);
		components = components->next;
	}
	return (remove_empty_command(&components1), parser(components1, info, env),
		free_node(components1));
}
