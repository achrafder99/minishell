/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:33:23 by aalami            #+#    #+#             */
/*   Updated: 2023/04/14 02:07:03 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*is_positif(int c)
{
	size_t	i;
	char	*p;
	int		tmp;

	tmp = c;
	i = 0;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		i++;
	}
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	p[i] = '\0';
	i--;
	while (c > 0)
	{
		p[i] = (c % 10) + 48;
		c = c / 10;
		i--;
	}
	return (p);
}

static char	*is_zero(void)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * 2);
	if (!p)
		return (NULL);
	p[i] = '0';
	p[i + 1] = '\0';
	return (p);
}

static char	*is_negatif(int c)
{
	size_t		i;
	char		*p;
	long int	tmp;
	long int	c_long;

	i = 0;
	c_long = (long int)c * -1;
	tmp = c_long;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		i++;
	}
	p = (char *)malloc(i + 2);
	if (!p)
		return (NULL);
	p[i + 1] = '\0';
	while (c_long > 0)
	{
		p[i] = (c_long % 10) + 48;
		c_long = c_long / 10;
		i--;
	}
	p[i] = '-';
	return (p);
}

char	*ft_itoa(int c)
{
	char	*p;

	if (c > 0)
	{
		p = is_positif(c);
		return (p);
	}
	else if (c == 0)
	{
		p = is_zero();
		return (p);
	}
	else
	{
		p = is_negatif(c);
		return (p);
	}
}
