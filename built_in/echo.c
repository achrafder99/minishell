/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/05/25 21:15:58 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_val(char *string, t_info *info, t_env *env)
{
	char	*key;
	int		until_dollar;
	char	*value_env;

	key = ft_strtrim(string, " \'");
	until_dollar = ft_strcspn(string, "$");
	value_env = extract_value(info, env, key + until_dollar);
	if (value_env == NULL)
	{
		free(key);
		key = NULL;
		return (ft_strdup("\'\'"));
	}
	free(key);
	key = NULL;
	return (value_env);
}

char	*get_env_val(char *string, t_info *info, t_env *env)
{
	char	*value_env;
	char	*value;
	int		length;
	int		i;
	int		j;

	value_env = get_val(string, info, env);
	length = ft_strlen(value_env);
	if (length == 2)
	{
		free(string);
		return (value_env);
	}
	value = malloc(sizeof(char) * length + 3);
	value[0] = '\'';
	i = 0;
	j = 0;
	while (++i <= length)
		value[i] = value_env[j++];
	value[i] = '\'';
	value[i + 1] = '\0';
	free(string);
	free(value_env);
	return (value);
}

int	echo(t_command *cmd, t_env *env, t_info *info)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	if (cmd->argc == 0)
		return (write(1, "\n", 1), 1);
	while (cmd->args[i] != NULL && !ft_strcmp(cmd->args[i], "-n"))
	{
		flags = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		if (cmd->args[i][0] == '\'' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '\'' && ft_strchr(cmd->args[i], '$'))
			cmd->args[i] = get_env_val(cmd->args[i], info, env);
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		write(1, " ", 1);
	}
	if (!flags)
		write(1, "\n", 1);
	return (0);
}
