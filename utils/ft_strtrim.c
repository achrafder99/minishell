/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:52:08 by adardour          #+#    #+#             */
/*   Updated: 2023/05/24 23:39:29 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*no_occurence(void)
{
	char	*new;

	new = malloc(sizeof(char));
	if (!new)
		return (0);
	*new = '\0';
	return (new);
}

static int	start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			break ;
		i++;
	}
	return (i);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = ft_strlen(set) - 1;
		while (j >= 0)
		{
			if (set[j] == s1[i])
				break ;
			j--;
		}
		if (j < 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	int		j;
	size_t	len;
	int		index;
	char	*new;

	if (!s1)
		return (0);
	index = 0;
	i = start(s1, set);
	if (i == ft_strlen(s1))
	{
		new = no_occurence();
		return (new);
	}
	j = end(s1, set);
	len = (j - i) + 1;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (len--)
		new[index++] = *(s1 + (i++));
	new[index] = '\0';
	return (new);
}
