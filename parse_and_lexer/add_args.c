/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:42:18 by adardour          #+#    #+#             */
/*   Updated: 2023/04/03 04:42:27 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **add_args(t_command *command,char *cut_str)
{
    char **new_args;
    command->argc += 1;
    new_args = (char**) malloc((command->argc + 1) * sizeof(char*));
    if (command->args) {
        ft_memcpy(new_args, command->args, (command->argc - 1) * sizeof(char*));
        free(command->args);
    }
    new_args[command->argc - 1] = cut_str;
    new_args[command->argc] = NULL;
    return (new_args);
}