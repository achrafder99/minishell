/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:44:14 by adardour          #+#    #+#             */
/*   Updated: 2023/04/03 04:44:21 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int open_in(t_command *command,char *infile)
{
    int fd;
    command->infile = infile;
    fd = open(command->infile, O_RDONLY,0777);				
    if(fd == -1){
        char *error;
        error = ": No such file or directory\n";
        write(2,command->infile,ft_strlen(command->infile));
        write(2,error,ft_strlen(error));
        return (-1);
    }
    close(fd);
    return (0);
}