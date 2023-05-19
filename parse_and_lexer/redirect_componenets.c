/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_componenets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 04:41:36 by adardour          #+#    #+#             */
/*   Updated: 2023/05/19 00:02:35 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_componenets(char **spliting, int *i, t_components **head,
		t_info *info)
{
	if (!ft_strcmp(spliting[*i], "<"))
		push_component(head, "REDIRECT_in", spliting, i, info);
	else if (!ft_strcmp(spliting[*i], ">"))
		push_component(head, "REDIRECT_out", spliting, i, info);
	else if (!ft_strcmp(spliting[*i], ">>"))
		push_component(head, "APPEND_MODE", spliting, i, info);
	else if (!ft_strcmp(spliting[*i], "<<"))
		push_component(head, "HEREDOC", spliting, i, info);
}
