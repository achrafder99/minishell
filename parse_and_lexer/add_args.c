/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:42:18 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 21:03:58 by adardour         ###   ########.fr       */
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

    free(command->args);  // Free the existing command->args
    command->args = new_args;  // Assign new_args to command->args

    return new_args;
}