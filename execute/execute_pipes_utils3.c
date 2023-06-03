/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:39:42 by aalami            #+#    #+#             */
/*   Updated: 2023/05/29 16:56:51 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_for_last_cmd(int i, t_piped *piping, int **fd, t_info *info)
{
	if (i + 1 == piping->number_of_commands)
		wait_for_last_exit(info->id[i], fd, info, &piping->command[i]);
}
