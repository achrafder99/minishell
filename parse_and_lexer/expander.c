/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/11 13:58:20 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_is_matched(char *pattern)
{
	int				flag;
	DIR				*dir;
	t_regex			*regex;
	struct dirent	*entry;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	flag = 0;
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))	
			return (1);
		entry = readdir(dir);
	}
	free(regex);
	free(regex->pattern);
	closedir(dir);
	return (0);
}

void	extract_matched_file(char *pattern,char *type,t_components **components1)
{
	int				flag;
	DIR				*dir;
	t_regex			*regex;
	struct dirent	*entry;

	regex = compile_regex(pattern);
	dir = opendir(".");
	entry = readdir(dir);
	flag = 0;
	while (entry != NULL)
	{
		if (match_regex(regex, entry->d_name))	
		{
			if (!flag)
			{
				push(components1,entry->d_name,type);
				flag = 1;
			}
			else
				push(components1,entry->d_name,"ARG");
		}
		entry = readdir(dir);
	}
	free(regex);
	free(regex->pattern);
	closedir(dir);
}

void    expander(t_components *node, \
t_env *env, t_info *info)
{
	t_components				*components;
	t_components				*components1;
	char						*temp;
	char						**spliting;
	int							i;
	int							position;
	char						*token;

	components1 = NULL;
	position = 0;
	components = node;
	while (components != NULL)
	{	
		if (ft_strchr(components->token,'*') && check_is_matched(components->token))
			extract_matched_file(components->token,components->type.type,&components1);
		else if (ft_strchr(components->token, '$') \
		&& ft_strcmp(components->type.type, "END_HEREDOC"))
		{	
			token = components->token;
			if (token[0] != '\'' && token[ft_strlen(token) - 1] != '\'')
			{
				components->token = ft_strtrim(components->token,"\"");
				temp = extract(components, env,info);
				if (temp)
				{
					spliting = ft_split(temp, ' ');
					push(&components1, spliting[0], components->type.type);
					i = 1;
					while (spliting[i])
					{
						push(&components1, spliting[i], "ARG");
						i++;
					}
				}
				else
					push(&components1, "", components->type.type);
			}
			else
				push(&components1, ft_strtrim(token,"\'"), components->type.type);
		}
		else
			push(&components1, components->token, components->type.type);
		components = components->next;
	}
	// while (components1)
	// {
	// 	printf("Token (%s) Type (%s)\n",components1->token,components1->type.type);
	// 	components1 = components1->next;
	// }
	// return;
	parser(components1, info, env);
	free_node(components1);
}
