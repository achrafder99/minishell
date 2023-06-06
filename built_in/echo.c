/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/06/02 22:30:52 by adardour         ###   ########.fr       */
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

int	validate_echo_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	else if (arg[i] == '-' && arg[i + 1] == '\0')
		return (0);
	else
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
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

	i = -1;
	flags = 0;
	if (cmd->argc == 0)
		return (write(1, "\n", 1), 1);
	while (cmd->args[++i] != NULL && validate_echo_option(cmd->args[i]))
		flags = 1;
	while (cmd->args[i] != NULL)
	{
		if (cmd->args[i][0] == '\'' && cmd->args[i][ft_strlen(cmd->args[i])
			- 1] == '\'' && ft_strchr(cmd->args[i], '$'))
			cmd->args[i] = get_env_val(cmd->args[i], info, env);
		if (cmd->args[i][0] != '.')
			write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
		if (cmd->args[i] != NULL)
			write(1, " ", 1);
	}
	if (!flags)
		write(1, "\n", 1);
	return (0);
}
