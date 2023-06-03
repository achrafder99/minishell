/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:43:48 by adardour          #+#    #+#             */
/*   Updated: 2023/06/02 18:31:36 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_exit_status(char *status_exit, int *i, int *j, char *string)
{
	size_t	index;

	index = 0;
	while (index < ft_strlen(status_exit))
	{
		string[(*i)++] = status_exit[index];
		index++;
	}
	(*j) += 2;
}

char	*end(char *result, char *concat, char *join, char *token)
{
	if (result == NULL && !join)
		concat = NULL;
	else
		concat = ft_strjoin(join, result);
	if (!join)
	{
		free(token);
		token = NULL;
		free(result);
		result = NULL;
		return (concat);
	}
	if (result)
	{
		free(result);
		result = NULL;
	}
	if (token)
	{
		free(token);
		token = NULL;
	}
	free(join);
	join = NULL;
	return (concat);
}

char	*get_exit_status(char *string, t_info *info)
{
	int		i;
	int		length;
	int		j;
	char	*status_exit;
	char	*str;

	status_exit = ft_itoa(info->status_code);
	length = (ft_strlen(string) - count(string)) + (ft_strlen(status_exit)
			* count(string) / 2);
	str = malloc(sizeof(char) * (length + 1));
	i = 0;
	j = 0;
	while (i < length && string[j] != '\0')
	{
		if (string[j] == '$' && string[j + 1] == '?')
			add_exit_status(status_exit, &i, &j, str);
		while (string[j] != '$' && string[j] != '\0')
			str[i++] = string[j++];
		if (string[j] == '$' && string[j + 1] != '?')
			str[i++] = string[j++];
	}
	str[length] = '\0';
	free(status_exit);
	return (str);
}

char	*until_dollar_sign(char *token)
{
	char	*before_dollar;
	int		string_size;
	int		inside_single_quotes;
	int		i;

	inside_single_quotes = 0;
	string_size = 0;
	i = -1;
	while (token[++i] != '\0')
	{
		if (token[i] == '\'')
			inside_single_quotes = !inside_single_quotes;
		else if (token[i] == '$' && !inside_single_quotes)
		{
			string_size = i;
			break ;
		}
	}
	before_dollar = malloc(sizeof(char) * (string_size + 1));
	if (!before_dollar)
	{
		perror("");
		exit(1);
	}
	return (ft_strncpy(before_dollar, token, string_size));
}

char	*extract(char *compo, t_env *env, t_info *info)
{
	char	*join;
	char	*concat;
	char	*token;
	char	*exit;
	char	*result;

	exit = NULL;
	join = NULL;
	result = NULL;
	concat = NULL;
	if (ft_strstr(compo, "$?"))
		exit = get_exit_status(compo, info);
	if (!ft_strchr(exit, '$') && exit)
		return (exit);
	if (exit && ft_strchr(exit, '$'))
		token = exit;
	else
		token = ft_strdup(compo);
	if (token[0] != '$')
		join = until_dollar_sign(token);
	result = proccess(env, info, token);
	return (end(result, concat, join, token));
}
