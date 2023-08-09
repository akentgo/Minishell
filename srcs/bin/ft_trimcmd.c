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
static int	n_words(const char *str, char *sep, int ct[2])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (str[ct[0]] != '\0')
	{
		if (!ft_strchr(sep, str[ct[0]]))
		{
			ct[1]++;
			while ((!ft_strchr(sep, str[ct[0]]) || q[0]) && str[ct[0]] != '\0')
			{
				if (!q[1] && (str[ct[0]] == '\"' || str[ct[0]] == '\''))
					q[1] = str[ct[0]];
				q[0] = (q[0] + (str[ct[0]] == q[1])) % 2;
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

static char	**ft_fill_array(char *str, char **ret, char *sep, int i[3])
{
	int	len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(sep, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(sep, str[i[0]]) || q[0] || q[1]) && q[i[0]])
		{
			q[0] = (q[0] + (!q[1] && str[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			ret[i[2]++] = "\0";
		else
			ret[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (ret);
}

char	**ft_trimcmd(char const *str, char *sep)
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
	if (!str)
		return (NULL);
	wd_ct = n_words(str, sep, ct);
	if (wd_ct == -1)
		return (NULL);
	ret = malloc ((wd_ct + 1) * sizeof (char *));
	if (!ret)
		return (NULL);
	ret = ft_fill_array((char *)str, ret, sep, i);
	ret[wd_ct] = NULL;
	return (ret);
}
