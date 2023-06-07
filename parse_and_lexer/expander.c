/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/06/07 01:36:33 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	just_check(t_components *components)
{
	return (components->token[0] == '\"'
		&& components->token[ft_strlen(components->token) - 1] == '\"'
		&& (components->token[1] == '\''
			&& components->token[ft_strlen(components->token) - 2] == '\''));
}

void	dont_expand(t_components *components, t_components **components1)
{
	char				*token;
	static unsigned int	track;

	token = components->token;
	if (track == 0 && !ft_strcmp(components->type.type, "COMMAND"))
	{
		push(components1, token, "COMMAND");
		track++;
	}
	else if (track == 0 && !ft_strcmp(components->type.type, "ARG"))
	{
		push(components1, token, "COMMAND");
		track++;
	}
	else
		push(components1, token, components->type.type);
	if (components->next == NULL)
		track = 0;
}

void	split_value(t_components *components, char *temp,
		t_components **components1)
{
	char	**spliting;
	int		i;

	spliting = split_token(temp, ' ');
	push(components1, spliting[0], components->type.type);
	i = 1;
	while (spliting[i])
	{
		push(components1, spliting[i], "ARG");
		i++;
	}
	free_things(spliting);
	free(temp);
	temp = NULL;
}

void	extract_dollar_sign(t_components *components, t_env *env, t_info *info,
		t_components **components1)
{
	char	*temp;

	temp = NULL;
	if (just_check(components))
		push(components1, components->token, components->type.type);
	else if (components->token[0] != '\''
		&& components->token[ft_strlen(components->token) - 1] != '\'')
	{
		temp = extract(components->token, env, info);
		if (temp != NULL)
			split_value(components, temp, components1);
		else if (!ft_strcmp(components->type.type, "COMMAND")
			&& components->next != NULL && temp == NULL
			&& !ft_strcmp(components->next->type.type, "PIPE"))
		{
			free(components->next->token);
			free(components->next->type.type);
			free(components->next);
			components->next = components->next->next;
		}
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

	if (!check_if_qouted(node))
	{
		info->status_code = 1;
		return ((void)write(2, "tsh : close qoutation \n", 24));
	}
	components = node;
	components1 = NULL;
	while (components != NULL)
	{
		if (ft_strchr(components->token, '*')
			&& check_is_matched(components->token))
			extract_matched_file(components->token, components->type.type,
				&components1);
		else if (ft_strchr(components->token, '$')
			&& ft_strcmp(components->type.type, "END_HEREDOC")
			&& ft_strcmp(components->token, "$"))
			extract_dollar_sign(components, env, info, &components1);
		else
			dont_expand(components, &components1);
		components = components->next;
	}
	return (parser(components1, info, env));
}
