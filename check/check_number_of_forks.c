/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number_of_forks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:31:29 by adardour          #+#    #+#             */
/*   Updated: 2023/05/22 13:24:49 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_number_forks(t_components *node)
{
	t_components	*proccess;
	int				proc;

	proccess = node;
	proc = 0;
	while (proccess)
	{
		if (!ft_strcmp(proccess->type.type, "PIPE"))
			proc++;
		proccess = proccess->next;
	}
	return (proc);
}
