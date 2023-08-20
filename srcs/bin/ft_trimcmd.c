/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:01:38 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:14:16 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * This function will count the number of words 
 after trimming, explained in lexer.c
 */
static int	n_words(const char *s, char *sep, int ct[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[ct[0]] != '\0')
	{
		if (!ft_strchr(sep, s[ct[0]]))
		{
			ct[1]++;
			while ((!ft_strchr(sep, s[ct[0]]) || q[0]) && s[ct[0]] != '\0')
			{
				if (!q[1] && (s[ct[0]] == '\"' || s[ct[0]] == '\''))
					q[1] = s[ct[0]];
				q[0] = (q[0] + (s[ct[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				ct[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			ct[0]++;
	}
	return (ct[1]);
}

/*
 * This will fill the array with the trimmed result, explained in lexer
 */

static char	**ft_fill_array(char *s, char **ret, char *sep, int i[3])
{
	int	len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(sep, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(sep, s[i[0]]) || q[0] || q[1]) && q[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			ret[i[2]++] = "\0";
		else
			ret[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (ret);
}

char	**ft_trimcmd(char const *s, char *sep)
{
	char	**ret;
	int		wd_ct;
	int		i[3];
	int		ct[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	ct[0] = 0;
	ct[1] = 0;
	if (!s)
		return (NULL);
	wd_ct = n_words(s, sep, ct);
	if (wd_ct == -1)
		return (NULL);
	ret = malloc ((wd_ct + 1) * sizeof (char *));
	if (!ret)
		return (NULL);
	ret = ft_fill_array((char *)s, ret, sep, i);
	ret[wd_ct] = NULL;
	return (ret);
}
