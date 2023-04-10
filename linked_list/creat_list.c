/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:22:52 by aalami            #+#    #+#             */
/*   Updated: 2023/04/10 02:24:23 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst	*creat_list()
{
	t_lst *a;
	a = malloc(sizeof(t_lst));
	a->top = NULL;
	return (a);
}

t_env	*creat_env()
{
	t_env *a;
	a = malloc(sizeof(t_env));
	a->top = NULL;
	return (a);
}

