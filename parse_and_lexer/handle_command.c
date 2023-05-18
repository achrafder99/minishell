/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 06:48:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/17 17:29:48 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_argument(t_components **node,char *cmd)
{
	t_components *temp;
	char 		**args;
	int			i;
	int			number_of_args;

	number_of_args = 0;
	temp = *node;
	while (temp && ft_strcmp(temp->type.type,"PIPE"))
	{
		if (!ft_strcmp(temp->type.type,"OPTION") || !ft_strcmp(temp->type.type,"ARG"))
			number_of_args++;
		temp = temp->next;
	}
	i = 0;
	temp = *node;
	args = (char**)malloc((sizeof(char*) * number_of_args) + 1);
	if (!args)
	{
		perror("");
		exit(1);
	}
	while (i < number_of_args && temp && ft_strcmp(temp->type.type,"PIPE"))
	{
		if (!ft_strcmp(temp->type.type,"OPTION") || !ft_strcmp(temp->type.type,"ARG"))
		{
			args[i] = ft_strdup(temp->token);
			i++;
		}
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

void	handler_heredoc(t_command **command, int *fd, t_components *node)
{
	if ((*command)->heredoc_lst == NULL)
		(*command)->heredoc_lst = creat_heredoc_list();
	ft_add_heredoc((*command)->heredoc_lst, new_heredoc(node->token, node->next->token));
	free((*command)->last_in);
	free((*command)->in_type);
	(*command)->last_in = ft_strdup(node->next->token);
	(*command)->in_type = ft_strdup(node->type.type);
}

void	handle_append(t_command **command, int *fd, t_components *node)
{
	*fd = open((*command)->last_out , O_CREAT, 0777);
	close(*fd);
	free((*command)->last_out);
	free((*command)->out_type);
	(*command)->last_out = ft_strdup(node->next->token);
	(*command)->out_type = ft_strdup(node->type.type);
}

void	handle_redirect(t_command **command, \
t_components *node, int *fd, t_info *info)
{
	if (!ft_strcmp(node->type.type, "REDIRECT_in"))
	{
		free((*command)->last_in);
		free((*command)->in_type);
		(*command)->last_in = ft_strdup(node->next->token);
		(*command)->in_type = ft_strdup(node->type.type);
		if (open_in(*command, node->next->token) == 1)
		{
			info->status_code = 1;
			return ;
		}
	}
	if (!ft_strcmp(node->type.type, "REDIRECT_out"))
	{
		free((*command)->last_out);
		free((*command)->out_type);
		(*command)->last_out = ft_strdup(node->next->token);
		(*command)->out_type = ft_strdup(node->type.type);
		*fd = open((*command)->last_out ,O_RDONLY | O_CREAT, 0777);
		close(*fd);
	}
	
}

int	get_size_of_args(char **argument)
{
	int size;
	size = 0;
	while (argument[size])
		size++;
	return (size);
}

void	handle_command(t_components *node, t_command **command, t_info *info)
{
	int			fd;
	static int last_flag;
	
	if (check_is_redirection(node->token) && !info->flags)
	{	
		*command = init_command(*command, node->token);
		info->flags = 1;
	}
	if (!ft_strcmp(node->type.type, "COMMAND") && info->flags)
	{
		*command = init_command(*command, node->token);
		(*command)->args = add_argument(&node,node->token);
		(*command)->argc = get_size_of_args((*command)->args);
	}
	else if (check_type(node->type.type))
	{
		if (!ft_strcmp(node->token, "<") || !ft_strcmp(node->token, ">"))
			handle_redirect(command, node, &fd, info);
		if (!ft_strcmp(node->token, ">>"))
			handle_append(command, &fd, node);
		if (!ft_strcmp(node->type.type, "HEREDOC"))	
			handler_heredoc(command, &fd, node);

	}
}