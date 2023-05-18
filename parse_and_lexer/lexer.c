/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:02:51 by adardour          #+#    #+#             */
/*   Updated: 2023/05/18 22:41:54 by aalami           ###   ########.fr       */
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
	process_push_redirection(spliting, head, i, info);
}

void	lexer(char *input, t_components **head, t_info *info, t_env *env)
{
	char	**spliting;
	int		i;

	i = 0;
	spliting = split_input(input);
	if (check_is_redirection(spliting[0]))
		lex1(spliting, head, i,info);
	else
		process_push_command(spliting, head, i, info);
    return (free_things(spliting),expander(*head, env, info),free_node(*head));
}
