/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:03:58 by akent-go          #+#    #+#             */
/*   Updated: 2022/04/27 10:51:38 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			start;
	size_t			len;
	size_t			i;

	start = 0;
	while (is_in_set(s1[start], (char *) set))
		start++;
	len = 0;
	i = 0;
	while (s1[start + i])
	{
		if (!is_in_set(s1[start + i], (char *) set))
			len = i + 1;
		i++;
	}
	return (ft_substr(s1, start, len));
}
