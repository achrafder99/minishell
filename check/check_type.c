/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:40:46 by adardour          #+#    #+#             */
/*   Updated: 2023/04/03 04:41:06 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_type(char *type){
    return (
    !ft_strcmp(type,"REDIRECT_in") 
    || !ft_strcmp(type,"REDIRECT_out")
    || !ft_strcmp(type,"APPEND_MODE")
    || !ft_strcmp(type,"HEREDOC"));
}