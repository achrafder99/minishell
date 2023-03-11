/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:52:08 by adardour          #+#    #+#             */
/*   Updated: 2023/03/11 16:52:23 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	beginning(char const *str, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (str[i] == set[j])
				break ;
			j++;
		}
		if (ft_strchr(set, str[i + 1]) == 0)
			break ;
		i++;
	}
	if (i > 0)
		i += 1;
	return (i);
}

static int	end(char const *str, char const *set)
{
	int	endindex;
	int	j;

	endindex = ft_strlen(str);
	while (endindex)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (str[endindex] == set[j])
				break ;
			j++;
		}
		if (ft_strchr(set, str[endindex - 1]) == 0)
			break ;
		endindex--;
	}
	return (endindex);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beginindex;
	int		endindex;
	char	*substr;
	int		len;
	int		i;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	beginindex = beginning(s1, set);
	endindex = end(s1, set);
	len = ft_strlen(s1) - (beginindex + (ft_strlen(s1) - endindex));
	if (len < 0)
		len = 0;
	substr = malloc((sizeof(char) * len) + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len)
	{
		substr[i] = s1[beginindex];
		i++;
		beginindex++;
	}
	substr[i] = '\0';
	return (substr);
}