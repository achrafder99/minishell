/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 04:56:34 by adardour          #+#    #+#             */
/*   Updated: 2023/04/09 05:57:11 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_regex	*compile_regex(const char *pattern)
{
	t_regex	*regex;

	regex = malloc(sizeof(regex));
	if (!regex)
		return (NULL);
	regex->pattern = ft_strdup(pattern);
	return (regex);
}

int	is_match(const char *pattern, int pattern_len, const char *input, int input_len)
{
	int	p;
	int	i;

	i = 0;
    p = 0;
	while (p < pattern_len && i < input_len)
	{
		if (pattern[p] == '*')
		{
			while (p < pattern_len && pattern[p] == '*')
                p++;
			if (p == pattern_len)
				return (1);
			while (i < input_len && input[i] != pattern[p])
                i++;
		}
		else if (pattern[p] == '?' || pattern[p] == input[i])
		{
            p++;
            i++;
		}
		else
			return (0);
	}
	while (p < pattern_len && pattern[p] == '*')
        p++;
	return (p == pattern_len && i == input_len);
}

int	match_regex(t_regex *regex, const char *input)
{
	const char	*pattern;
	int			pattern_len;
	int			input_len;

	if (!regex || !regex->pattern || !input)
		return (0);
	pattern = regex->pattern;
	pattern_len = ft_strlen(pattern);
	input_len = ft_strlen(input);
	return (is_match(pattern, pattern_len, input, input_len));
}
