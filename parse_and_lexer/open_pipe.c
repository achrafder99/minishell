/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:26:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/21 18:03:27 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	just_free(char **spliting, char *cmd)
{
	free_things(spliting);
	free(cmd);
}

int	size(char **spliting)
{
	int	size;

	size = 0;
	while (spliting[size])
		size++;
	return (size);
}

void	add_token(char **spliting, t_components **head, int i, t_info *info)
{
	while (spliting[i])
	{
		if (spliting[i][0] == '-')
			push(head, spliting[i], "OPTION");
		else if (!ft_strcmp(spliting[i], "|"))
		{
			info->flags = 0;
			if (!check_is_redirection(spliting[i + 1]))
				info->flags = 1;
			info->type = "PIPE";
			push_component(head, spliting, &i, info);
		}
		else if (check_is_redirection(spliting[i]))
			redirect_componenets(spliting, &i, head, info);
		else
			push(head, spliting[i], "ARG");
		i++;
	}
}

void	split_cmd(char *cmd, char **spliting, t_components **head, t_info *info)
{
	int	i;

	i = 0;
	if (!check_is_redirection(spliting[0]))
	{
		push(head, spliting[0], "COMMAND");
		i = 1;
	}
	add_token(spliting, head, i, info);
}

int	open_pipe(t_components **head, t_info *info)
{
	char	*error;

	while (1)
	{
		info->token = readline("> ");
		if (info->token == NULL)
		{
			error = "tsh: syntax error: unexpected end of file\n";
			return (write(2, error, ft_strlen(error)), 258);
		}
		if (ft_strlen(info->token) != 0)
		{
			info->spliting = split_input(info->token);
			split_cmd(info->token, info->spliting, head, info);
			if (ft_strcmp(info->spliting[size(info->spliting) - 1], "|"))
			{
				just_free(info->spliting, info->token);
				break ;
			}
		}
		else
			free(info->token);
	}
	return (0);
}
