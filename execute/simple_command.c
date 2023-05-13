/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:41:27 by adardour          #+#    #+#             */
/*   Updated: 2023/05/13 20:27:09 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern char	**environ;

t_here_node	*last_here_node(t_here_data *lst)
{
	t_here_node	*tmp;

	if (lst->top == NULL)
		return (0);
	tmp = lst->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_here_node	*new_here_node(char *data)
{
	t_here_node	*node;

	node = malloc(sizeof(t_here_node));
	if (!(node))
		return (0);
	node->data = ft_strdup(data);
	node->next = NULL;
	return (node);
}

void	ft_add_here_data(t_here_data *lst, t_here_node *new)
{
	t_here_node	*tmp;

	if (!new)
		return ;
	if (!lst->top)
		lst->top = new;
	tmp = last_here_node(lst);
	tmp->next = new;
	new->next = 0;
}

t_here_data	*creat_heredoc_data_list(void)
{
	t_here_data	*lst;

	lst = malloc(sizeof(t_here_lst));
	if (!lst)
		return (0);
	lst->top = NULL;
	return (lst);
}

t_here_data	*open_heredoc(t_here_lst *list)
{
	t_heredoc	*tmp;
	t_here_data	*data_lst;
	t_here_node	*node;
	char		*data;
	int			flag;

	tmp = list->top;
	flag = 0;
	data_lst = NULL;
	while (tmp)
	{
		if (!tmp->next)
		{
			data_lst = creat_heredoc_data_list();
			flag = 1;
		}
		while (1)
		{
			data = readline(">");
			if (!data)
				break ;
			if (ft_strcmp(data, tmp->delimit))
			{
				if (flag)
				{
					node = new_here_node(data);
					ft_add_here_data(data_lst, node);
				}
			}
			else
				break ;
			free(data);
		}
		tmp = tmp->next;
	}
	return (data_lst);
}
void	first_step(t_command *command, t_info *info, int *built_in, int *flags,
		t_env *env)
{
	int		save;
	t_fds	*fds;

	if (!check_command(command->name, env))
	{
		printf("minishell: %s: No such file or directory\n", command->name);
		info->status_code = 127;
		*flags = 127;
		return ;
	}
	save = -1;
	if (command->last != NULL)
	{
		if (check_type(command->last->in_type)
			|| check_type(command->last->out_type))
			*flags = 1;
	}
	if (check_is_built_in(command->name))
	{
		if (*flags)
		{
			if (command->last->last_in)
				save = dup(STDIN_FILENO);
			else if (command->last->last_out)
				save = dup(STDOUT_FILENO);
			redirection(command, command->data_lst);
		}
		execute_built_in(command, info, env);
		if (save != -1)
		{
			if (command->last->last_in)
				dup2(save, STDIN_FILENO);
			else if (command->last->last_out)
				dup2(save, STDOUT_FILENO);
		}
		*built_in = 1;
	}
}

void	run_child(t_command *command, int flags, int built_in, char **argv,
		t_env *env)
{
	t_fds	*fds;
	char	*cmd;

	if (flags)
		redirection(command, command->data_lst);
	cmd = get_cmd(command->name);
	execve(cmd, argv, env->env_arr);
}
int	get_list_size(t_lst *lst)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = lst->top;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
char	**get_new_env(t_lst *env)
{
	char	**new;
	char	*key;
	t_node	*tmp;
	int		size;
	int		i;

	size = get_list_size(env);
	tmp = env->top;
	i = 0;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			new[i] = ft_strjoin(key, tmp->value);
		else
			new[i] = ft_strdup(key);
		free(key);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	simple_command(t_command *command, t_info *info, t_env *env)
{
	char	**argv;
	int		fid;
	int		flags;
	int		built_in;
	char	**spliting;

	argv = get_argv(command, command->argc);
	flags = 0;
	built_in = 0;
	if (command->heredoc_lst)
		command->data_lst = open_heredoc(command->heredoc_lst);
	first_step(command, info, &built_in, &flags, env);
	if (built_in || flags == 127)
		return ;
	env->env_arr = get_new_env(env->env);
	if (command)
		fid = fork();
	if (fid == 0)
		run_child(command, flags, built_in, argv, env);
	else
	{
		waitpid(fid, &info->status_code, 0);
		if (WIFSIGNALED(info->status_code))
			info->status_code = WTERMSIG(info->status_code) + 128;
		else
			info->status_code = WEXITSTATUS(info->status_code);
	}
	unlink(".heredoc");
}
