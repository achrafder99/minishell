/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:22:52 by aalami            #+#    #+#             */
/*   Updated: 2023/05/13 20:29:08 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst	*creat_list(void)
{
	t_lst	*a;

	a = malloc(sizeof(t_lst));
	if (!a)
		return (0);
	a->top = NULL;
	return (a);
}

t_env	*creat_env(void)
{
	t_env	*a;

	a = malloc(sizeof(t_env));
	if (!a)
		return (0);
	a->env = NULL;
	a->exp = NULL;
	return (a);
}
