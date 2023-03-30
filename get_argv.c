/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:58:32 by adardour          #+#    #+#             */
/*   Updated: 2023/03/30 04:03:28 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char **get_argv(t_command *command, int number_arg) {
    char **argv;

    if (command->name && command->argc == 0) {
        argv = malloc(sizeof(char*) * 2);
        argv[0] = command->name;
        argv[1] = NULL;
        return argv;
    }

    argv = malloc(sizeof(char*) * (number_arg + 2));
    if (!argv)
        return NULL;
    argv[0] = command->name;
    for (int i = 1; i <= number_arg; i++) {
        argv[i] = malloc(sizeof(char) * (strlen(command->args[i-1]) + 1));
        if (!argv[i]) {
            for (int j = i-1; j >= 1; j--) {
                free(argv[j]);
            }
            free(argv);
            return NULL;
        }
        strcpy(argv[i], command->args[i-1]);
    }
    argv[number_arg+1] = NULL;
    return argv;
}