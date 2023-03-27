/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:58:32 by adardour          #+#    #+#             */
/*   Updated: 2023/03/27 19:58:47 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char **get_argv(t_command *command,int number_arg){
	char **argv;

	argv = malloc(sizeof(char*) * number_arg + 2);
	argv[0] = command->name;
	int i;
	i = 1;
	int j;
	j = 0;
	while (i <= number_arg)
	{
		argv[i] = command->args[j];
		i++;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}
