/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_componenets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 04:41:36 by adardour          #+#    #+#             */
/*   Updated: 2023/05/25 22:37:27 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_componenets(char **spliting, int *i, t_components **head,
		t_info *info)
{
	if (!ft_strcmp(spliting[*i], "<"))
	{
		info->type = "REDIRECT_in";
		push_component(head, spliting, i, info);
	}
	else if (!ft_strcmp(spliting[*i], ">"))
	{
		info->type = "REDIRECT_out";
		push_component(head, spliting, i, info);
	}
	else if (!ft_strcmp(spliting[*i], ">>"))
	{
		info->type = "APPEND_MODE";
		push_component(head, spliting, i, info);
	}
	else if (!ft_strcmp(spliting[*i], "<<"))
	{
		info->type = "HEREDOC";
		push_component(head, spliting, i, info);
	}
}
