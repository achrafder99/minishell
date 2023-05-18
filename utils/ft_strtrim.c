/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:52:08 by adardour          #+#    #+#             */
/*   Updated: 2023/04/08 20:02:26 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	set_len;
	size_t	start;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	s1_len = strlen(s1);
	set_len = strlen(set);
	start = 0;
	end = s1_len - 1;
	while (start < s1_len && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trimmed_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trimmed_str)
		return (NULL);
	strncpy(trimmed_str, s1 + start, end - start + 1);
	trimmed_str[end - start + 1] = '\0';
	return (trimmed_str);
}
