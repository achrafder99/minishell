/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:29:17 by adardour          #+#    #+#             */
/*   Updated: 2023/05/08 18:32:28 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_input(char *input)
{
	char	*str;
	char	*error;
	char	**spliting;
	int		i;

	i = 0;
	str = NULL;
	if (!check_quotes(input))
	{
		error = "Syntax Error: String must be closed\n";
		write(2, error, ft_strlen(error));
		return (NULL);
	}
	if (check_is_space(input))
		str = new_str(input, check_is_space(input));
	if (str)
		spliting = split_2(str);
	else
		spliting = split_2(input);
	free(str);
	return (spliting);
}
