/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:43:48 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 16:58:05 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			count += 2;
		i++;
	}
	return (count);
}

char	*get_exit_status(char *string, t_info *info)
{
	int		i;
	int		length;
	int		j;
	char	*status_exit;
	int		kkk;

	status_exit = ft_itoa(info->status_code);
	length = (ft_strlen(string) - count(string)) + ft_strlen(status_exit);
	info->token = malloc(sizeof(char) * (length + 1));
	i = 0;
	j = 0;
	while (i < length)
	{
		if (string[i] == '$' && string[i + 1] == '?')
		{
			kkk = 0;
			while (kkk < ft_strlen(status_exit))
				info->token[i++] = status_exit[kkk++];
			j += 2;
		}
		info->token[i++] = string[j++];
	}
	info->token[length] = '\0';
	free(status_exit);
	return (info->token);
}

char	*until_dollar_sign(char *token)
{
	char	*before_dollar;
	int		string_size;
	int		inside_single_quotes;
	int		i;

	inside_single_quotes = 0;
	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			inside_single_quotes = !inside_single_quotes;
		else if (token[i] == '$' && !inside_single_quotes)
		{
			string_size = i;
			break ;
		}
		i++;
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
	char	*ss1;

	join = NULL;
	if (ft_strchr(compo, '?'))
		token = get_exit_status(compo, info);
	else
		token = ft_strdup(compo);
	if (token[0] != '$' && ft_strchr(token, '$'))
		join = until_dollar_sign(compo);
	else
		return (token);
	ss1 = ft_strchr(token, '$');
	concat = proccess(token, env, info, ss1);
	if (concat == NULL || ft_strlen(concat) == 0)
		return (NULL);
	if (!join)
		return (concat);
	info->token = ft_strjoin(join, concat);
	free(token);
	free(join);
	return (info->token);
}
