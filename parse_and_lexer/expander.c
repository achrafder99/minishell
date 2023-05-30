/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:36 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dont_expand(t_components *components, t_components **components1)
{
	char	*token;

	token = components->token;
	push(components1, token, components->type.type);
}

void	split_value(t_components *components, char *temp,
		t_components **components1)
{
	char	**spliting;
	int		i;

	spliting = split_token(temp);
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

	temp = NULL;
	if (components->token[0] == '\"'
		&& components->token[ft_strlen(components->token) - 1] == '\"'
		&& (components->token[1] == '\''
			&& components->token[ft_strlen(components->token) - 2] == '\''))
		push(components1, components->token, components->type.type);
	else if (components->token[0] != '\''
		&& components->token[ft_strlen(components->token) - 1] != '\'')
	{
		temp = extract(components->token, env, info);
		if (temp != NULL)
		{
			split_value(components, temp, components1);
			free(temp);
			temp = NULL;
		}
		else
			push(components1, "", components->type.type);
	}
	else
		push(components1, components->token, components->type.type);
}

void	expander(t_components *node,
				t_env *env,
				t_info *info)
{
	t_components	*components;
	t_components	*components1;

	components = node;
	components1 = NULL;
	while (components != NULL)
	{
		if (ft_strchr(components->token, '*')
			&& check_is_matched(components->token))
			extract_matched_file(components->token, components->type.type, \
		&components1);
		else if (ft_strchr(components->token, '$')
			&& ft_strcmp(components->type.type, "END_HEREDOC")
			&& ft_strcmp(components->token, "$"))
			extract_dollar_sign(components, env, info, &components1);
		else
			dont_expand(components, &components1);
		components = components->next;
	}
	return (remove_empty_command(&components1), parser(components1, info, env),
		free_components(components1));
}
