/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:42:18 by adardour          #+#    #+#             */
/*   Updated: 2023/05/18 14:18:24 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **add_args(t_command *command, char *cut_str)
{
    char **new_args;

    command->argc += 1;
    new_args = (char **)malloc((command->argc + 1) * sizeof(char *));
    ft_memcpy(new_args, command->args, (command->argc - 1) * sizeof(char *));
    new_args[command->argc - 1] = cut_str;
    new_args[command->argc] = NULL;

<<<<<<< HEAD
    free(command->args);
    command->args = new_args;
    return (new_args);
=======
    if (command->args)
        free(command->args);  
    command->args = new_args;
    return new_args;
>>>>>>> 147926a5c80bf3e293af1805bb1be39a025d6bbb
}