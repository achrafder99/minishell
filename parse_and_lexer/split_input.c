/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 22:44:52 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_input(char *input)
{
	char	*str;
	char	*error;
	char	**spliting;

	str = NULL;
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		spliting = ft_split(str, ' ');
	else
		spliting = ft_split(input, ' ');
	if (!check_quotes(input))
	{
		error = "Syntax Error: String must be closed\n";
		write(2, error, ft_strlen(error));
		return (NULL);
	}
	free(str);
	return (spliting);
}
