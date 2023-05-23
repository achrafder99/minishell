/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:20:37 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 19:23:07 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		ptr[i] = s1[i];
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
