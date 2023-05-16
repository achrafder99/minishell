/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/05/14 16:56:45 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_components(t_components *head)
{
    t_components *current = head;
    t_components *next;

    while (current != NULL) {
        next = current->next;
        free(current->token);
        free(current->type.type);
        free(current);
        current = next;
    }
}

void	lex2(char **spliting, char *type, t_data *data)
{
	if (!ft_strcmp(spliting[0], ">>"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], "<<"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], ">"))
		lex_redirection(data);
	else if (!ft_strcmp(spliting[0], "<"))
		lex_redirection(data);
}

void	lex1(char **spliting, t_components **head, int i,t_info *info)
{
	t_data				data;
	int					flags;

	flags = 0;
	info->flags = 0;
	data = (t_data){.type = spliting[0], head, spliting, &i, &info->flags};
	lex2(spliting, data.type, &data);
	while (spliting[i] != NULL)
	{
		if (!ft_strcmp(spliting[i],"|"))
		{
			info->flags = 0;
			push_component(head, "PIPE", spliting, &i, info);
		}
		else if (check_is_redirection(spliting[i]))
		{
			redirect_componenets(spliting, &i, head,info);
			if (spliting[i + 1] != NULL && !info->flags \
			&& !check_is_redirection(spliting[i + 1]) 
			&& ft_strcmp(spliting[i + 1],"|"))
			{
				push(head, spliting[i + 1], "COMMAND");
				i++;
				info->flags = 1;
			}
		}
		else
			push(head, spliting[i], "ARG");
		i++;
	}
}

void	lexer(char *input, t_components **head, t_info *info, t_env *env)
{
	char	**spliting;
	int		i;
	
	i = 0;
	spliting = split_input(input);
	// while (spliting[i])
	// {
	// 	printf("%s\n",spliting[i]);
	// 	i++;
	// }
	// return;
	if (check_is_redirection(spliting[0]))
		lex1(spliting, head, i,info);
	else
	{

		push(head, spliting[0], "COMMAND");
		i = 1;
		while (spliting[i] != NULL)
		{
			if (spliting[i][0] == '-')
				push(head, spliting[i], "OPTION");
			else if (!ft_strcmp(spliting[i],"|"))
			{
				info->flags = 0;
				if (!check_is_redirection(spliting[i + 1]))
					info->flags = 1;
				push_component(head, "PIPE", spliting, &i,info);
			}
			else if (check_is_redirection(spliting[i]))
				redirect_componenets(spliting, &i, head, info);
			else
				push(head, spliting[i], "ARG");
			i++;
		}
	}
	expander(*head, env, info);
    free_things(spliting);
}
