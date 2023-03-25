/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:21:05 by adardour          #+#    #+#             */
/*   Updated: 2023/03/25 17:21:14 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	i = 0;
	if (n == 0)
		return (dest);
	else if (dest == NULL && source == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}